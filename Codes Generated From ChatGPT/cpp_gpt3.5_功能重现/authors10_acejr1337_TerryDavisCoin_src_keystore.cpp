#include <iostream>
#include <string>
#include <vector>

// ������Կ��
class CKey {
public:
    CKey(const std::string& privateKey, const std::string& publicKey) :
        m_privateKey(privateKey),
        m_publicKey(publicKey) {}

    std::string GetPrivateKey() const { return m_privateKey; }
    std::string GetPublicKey() const { return m_publicKey; }

private:
    std::string m_privateKey;
    std::string m_publicKey;
};

// ����ű���
class CScript {
public:
    CScript(const std::string& script) :
        m_script(script) {}

    std::string GetScript() const { return m_script; }

private:
    std::string m_script;
};

// ���������Կ�洢��
class CBasicKeyStore {
public:
    // �����Կ
    void AddKey(const CKey& key) {
        m_keys.push_back(key);
    }

    // ��ȡ��Կ
    CKey GetKey(const std::string& publicKey) const {
        for (const auto& key : m_keys) {
            if (key.GetPublicKey() == publicKey) {
                return key;
            }
        }

        // ����Ҳ�����Ӧ����Կ���򷵻ؿ���Կ
        return CKey("", "");
    }

    // ��ӽű�
    void AddScript(const CScript& script) {
        m_scripts.push_back(script);
    }

    // ��ȡ�ű�
    CScript GetScript(const std::string& script) const {
        for (const auto& s : m_scripts) {
            if (s.GetScript() == script) {
                return s;
            }
        }

        // ����Ҳ�����Ӧ�Ľű����򷵻ؿսű�
        return CScript("");
    }

    // �Զ�������ؽű�����������ӵ�������Կ�洢��
    void ImplicitlyLearnRelatedKeyScripts(const std::string& publicKey) {
        // TODO: ʵ����ؽű��Զ������߼�
    }

    // ��ӹ۲�ű�
    void AddWatchScript(const CScript& script) {
        m_watchScripts.push_back(script);
    }

    // ��ȡ�۲�ű�
    CScript GetWatchScript(const std::string& script) const {
        for (const auto& s : m_watchScripts) {
            if (s.GetScript() == script) {
                return s;
            }
        }

        // ����Ҳ�����Ӧ�Ĺ۲�ű����򷵻ؿսű�
        return CScript("");
    }

    // ��Ŀ���ַ��ȡ��Կ ID
    std::string ExtractPublicKeyID(const std::string& address) const {
        // TODO: ʵ�ִ�Ŀ���ַ��ȡ��Կ ID ���߼�
        return "";
    }

private:
    std::vector<CKey> m_keys;           // �洢��Կ������
    std::vector<CScript> m_scripts;     // �洢�ű�������
    std::vector<CScript> m_watchScripts;// �洢�۲�ű�������
};

int main() {
    // ����һ��������Կ�洢����
    CBasicKeyStore keyStore;

    // ���һЩ��Կ
    CKey key1("private1", "public1");
    CKey key2("private2", "public2");
    keyStore.AddKey(key1);
    keyStore.AddKey(key2);

    // ��ȡĳ����Կ
    CKey key = keyStore.GetKey("public1");
    std::cout << "PrivateKey: " << key.GetPrivateKey() << ", PublicKey: " << key.GetPublicKey() << std::endl;

    // ���һЩ�ű�
    CScript script1("script1");
    CScript script2("script2");
    keyStore.AddScript(script1);
    keyStore.AddScript(script2);

    // ��ȡĳ���ű�
    CScript script = keyStore.GetScript("script1");
    std::cout << "Script: " << script.GetScript() << std::endl;

    // ��ӹ۲�ű�
    CScript watchScript("watchscript");
    keyStore.AddWatchScript(watchScript);

    // ��ȡ�۲�ű�
    CScript watch = keyStore.GetWatchScript("watchscript");
    std::cout << "WatchScript: " << watch.GetScript() << std::endl;

    // ��ȡ��Կ ID
    std::string publicKeyID = keyStore.ExtractPublicKeyID("1A1zP1eP5QGefi2DMPTfTL5SLmv7DivfNa");
    std::cout << "PublicKeyID: " << publicKeyID << std::endl;

    return 0;
}
