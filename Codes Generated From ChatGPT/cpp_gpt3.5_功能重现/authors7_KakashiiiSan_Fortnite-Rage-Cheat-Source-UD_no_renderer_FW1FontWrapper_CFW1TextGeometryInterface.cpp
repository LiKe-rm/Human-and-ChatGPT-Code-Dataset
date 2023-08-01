#include <vector>
#include <algorithm>
#include <d3d11.h>
#include "FW1FontWrapper.h"

namespace FW1FontWrapper {

    struct FW1_VERTEXDATA {
        std::vector<FW1_GLYPHVERTEX> Vertices;
        UINT SheetIndex;
    };

    class CFW1TextGeometry : public IFW1TextGeometry {
    public:
        CFW1TextGeometry() : m_refCount(1) {}
        virtual ~CFW1TextGeometry() {}

        // IUnknown methods
        ULONG STDMETHODCALLTYPE AddRef() {
            return ++m_refCount;
        }

        ULONG STDMETHODCALLTYPE Release() {
            ULONG refCount = --m_refCount;
            if (refCount == 0)
                delete this;
            return refCount;
        }

        HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) {
            if (ppvObject == nullptr)
                return E_INVALIDARG;

            if (riid == __uuidof(IUnknown) || riid == __uuidof(IFW1TextGeometry)) {
                *ppvObject = this;
                AddRef();
                return S_OK;
            }

            *ppvObject = nullptr;
            return E_NOINTERFACE;
        }

        // IFW1TextGeometry methods
        void STDMETHODCALLTYPE Clear() {
            m_glyphVertices.clear();
        }

        HRESULT STDMETHODCALLTYPE AddGlyphVertex(const FW1_GLYPHVERTEX *pGlyphVertex) {
            if (pGlyphVertex == nullptr)
                return E_INVALIDARG;

            m_glyphVertices.push_back(*pGlyphVertex);
            return S_OK;
        }

        FW1_VERTEXDATA STDMETHODCALLTYPE GetGlyphVertices() {
            std::sort(m_glyphVertices.begin(), m_glyphVertices.end(), compareSheetIndex);

            FW1_VERTEXDATA vertexData;
            vertexData.Vertices = m_glyphVertices;
            vertexData.SheetIndex = m_glyphVertices.empty() ? 0 : m_glyphVertices.front().SheetIndex;

            return vertexData;
        }

    private:
        ULONG m_refCount;
        std::vector<FW1_GLYPHVERTEX> m_glyphVertices;

        static bool compareSheetIndex(const FW1_GLYPHVERTEX &a, const FW1_GLYPHVERTEX &b) {
            return a.SheetIndex < b.SheetIndex;
        }
    };

} // namespace FW1FontWrapper
