#include <iostream>
#include <thread>
#include <chrono>

class CKPListDataNode {
    // implementation of CKPListDataNode class
};

class CKPListDataNodeLoader {
private:
    CKPListDataNode* m_node;
    std::string m_name;
    bool m_threadDone;
    std::thread* m_thread;

    CKPListDataNodeLoader(CKPListDataNode* node, std::string name) :
        m_node(node), m_name(name), m_threadDone(false), m_thread(nullptr) {}

public:
    static void doLoad(CKPListDataNode* node, std::string name) {
        if (!node) {
            throw std::invalid_argument("CKPListDataNode cannot be null");
        }

        CKPListDataNodeLoader* loader = new CKPListDataNodeLoader(node, name);
        loader->m_thread = new std::thread(&CKPListDataNodeLoader::process, loader);

        if (!loader->m_thread) {
            throw std::runtime_error("Failed to start CKPListDataNodeLoader thread");
        }
    }

    static const int cDone = 0;
    static const int cError = -1;

    int operator==(const CKPListDataNodeLoader& other) const {
        return (m_name == other.m_name) && (m_node == other.m_node);
    }

    int operator!=(const CKPListDataNodeLoader& other) const {
        return !(*this == other);
    }

    std::string toString() const {
        std::string result = "CKPListDataNodeLoader[";
        result += "name=" + m_name + ",";
        result += "node=" + std::to_string(reinterpret_cast<intptr_t>(m_node)) + ",";
        result += "threadDone=" + std::to_string(m_threadDone) + "]";
        return result;
    }

    virtual ~CKPListDataNodeLoader() {}

private:
    void process() {
        if (!m_node) {
            throw std::invalid_argument("CKPListDataNode cannot be null");
        }

        m_node->load();

        if (!m_node->isLoaded()) {
            throw std::runtime_error("Failed to load CKPListDataNode");
        }

        m_threadDone = true;
        std::cout << "CKPListDataNodeLoader " << m_name << " loaded successfully\n";
    }

public:
    int terminate() {
        if (!m_threadDone) {
            return cError;
        }

        delete m_thread;
        m_thread = nullptr;

        delete this;
        return cDone;
    }
};
