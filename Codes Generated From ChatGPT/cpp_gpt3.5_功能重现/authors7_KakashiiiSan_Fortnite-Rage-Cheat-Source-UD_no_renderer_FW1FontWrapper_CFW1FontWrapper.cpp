// 导入需要的头文件
#include <d3d11.h>
#include <dwrite.h>
#include <FW1FontWrapper.h>
#include <memory>

// 声明FW1FontWrapper命名空间
namespace FW1FontWrapper {

	// 定义CFW1FontWrapper类
	class CFW1FontWrapper {
	public:
		// 构造函数
		CFW1FontWrapper();
		// 析构函数
		~CFW1FontWrapper();

		// 成员函数声明
		HRESULT initFontWrapper(ID3D11Device* pDevice, IDWriteGlyphRunAnalysis* pGlyphAnalysis,
			IDWriteGlyphRun* pGlyphRun, IDWriteGlyphRenderer* pGlyphRenderer,
			IDWriteRenderingParams* pRenderingParams, IDWriteFactory* pDWriteFactory,
			const FW1_FONTWRAPPERCREATEPARAMS* pFontParams);
		IDWriteTextLayout* createTextLayout(const wchar_t* text, const wchar_t* fontFamily, float fontSize,
			const DWRITE_TEXT_RANGE& layoutRect, UINT32 flags);

	private:
		// 私有成员变量声明
		ID3D11Device* m_pDevice;
		IDWriteGlyphRunAnalysis* m_pGlyphAnalysis;
		IDWriteGlyphRun* m_pGlyphRun;
		IDWriteGlyphRenderer* m_pGlyphRenderer;
		IDWriteRenderingParams* m_pRenderingParams;
		IDWriteFactory* m_pDWriteFactory;
		std::unique_ptr<FW1_FONTWRAPPERCREATEPARAMS> m_pFontParams;
		IDWriteTextFormat* m_pDefaultTextFormat;
	};

	// 构造函数实现
	CFW1FontWrapper::CFW1FontWrapper()
		: m_pDevice(nullptr), m_pGlyphAnalysis(nullptr), m_pGlyphRun(nullptr), m_pGlyphRenderer(nullptr),
		m_pRenderingParams(nullptr), m_pDWriteFactory(nullptr), m_pDefaultTextFormat(nullptr) {}

	// 析构函数实现
	CFW1FontWrapper::~CFW1FontWrapper() {
		if (m_pDefaultTextFormat) {
			m_pDefaultTextFormat->Release();
		}
	}

	// initFontWrapper实现
	HRESULT CFW1FontWrapper::initFontWrapper(ID3D11Device* pDevice, IDWriteGlyphRunAnalysis* pGlyphAnalysis,
		IDWriteGlyphRun* pGlyphRun, IDWriteGlyphRenderer* pGlyphRenderer,
		IDWriteRenderingParams* pRenderingParams, IDWriteFactory* pDWriteFactory,
		const FW1_FONTWRAPPERCREATEPARAMS* pFontParams) {
		// 存储指针到成员变量
		m_pDevice = pDevice;
		m_pGlyphAnalysis = pGlyphAnalysis;
		m_pGlyphRun = pGlyphRun;
		m_pGlyphRenderer = pGlyphRenderer;
		m_pRenderingParams = pRenderingParams;
		m_pDWriteFactory = pDWriteFactory;
		m_pFontParams.reset(new FW1_FONTWRAPPERCREATEPARAMS(*pFontParams));

		// 创建默认的文本格式对象
		HRESULT hr = m_pDWriteFactory->CreateTextFormat(pFontParams->pszFontFamily, nullptr,
			pFontParams->FontWeight, pFontParams->FontStyle,
			pFontParams->FontStretch, pFontParams->fFontSize,
			L"en-us", &m_pDefaultTextFormat);

		return hr;
	}

	// createTextLayout实现
	IDWriteTextLayout* CFW1FontWrapper::createTextLayout(const wchar_t* text, const wchar_t* fontFamily,
		float fontSize, const DWRITE_TEXT_RANGE& layoutRect, UINT32 flags) {
		IDWriteTextFormat* pTextFormat;
		HRESULT hr;
		// 如果指定了字体和字体大小，则创建新的文本格式对象；否则使用默认的文本格式对象
		if (fontFamily && fontSize > 0) {
			hr = m_pDWriteFactory->CreateTextFormat(fontFamily, nullptr, DWRITE_FONT_WEIGHT_NORMAL,
				DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, fontSize,
				L"en-us", &pTextFormat);
			if (FAILED(hr)) {
				return nullptr;
			}
		}
		else {
			pTextFormat = m_pDefaultTextFormat;
			pTextFormat->AddRef();
		}

		// 创建文本布局对象
		IDWriteTextLayout* pTextLayout;
		hr = m_pDWriteFactory->CreateTextLayout(text, wcslen(text), pTextFormat, layoutRect.right - layoutRect.left,
			layoutRect.bottom - layoutRect.top, &pTextLayout);

		// 释放临时创建的文本格式对象（如果有）
		pTextFormat->Release();

		if (SUCCEEDED(hr)) {
			return pTextLayout;
		}
		else {
			return nullptr;
		}
	}
} // namespace FW1FontWrapper
