#include <string>
#include <vector>
#include <memory>

// Page class
class Page {
public:
    int getCurrent() const { return current; }
    void setCurrent(int c) { current = c; }
    
    int getSize() const { return size; }
    void setSize(int s) { size = s; }
    
    int getTotal() const { return total; }
    void setTotal(int t) { total = t; }

private:
    int current = 0;
    int size = 0;
    int total = 0;
};

// StatusCode enumeration
enum class StatusCode {
    OK = 0,
    ERROR = 1,
};

// Result class
template <typename T>
class Result {
public:
    Result(StatusCode code = StatusCode::OK, std::string message = "")
        : code(code), message(message), data(nullptr) { }
    
    bool isSuccess() const {
        return code == StatusCode::OK;
    }
    
    static Result<T> ok() {
        return Result<T>(StatusCode::OK, "");
    }

    static Result<T> ok(StatusCode code, std::string message) {
        return Result<T>(code, message);
    }

    static Result<T> error() {
        return Result<T>(StatusCode::ERROR, "");
    }

    static Result<T> error(StatusCode code, std::string message) {
        return Result<T>(code, message);
    }
    
    static Result<T> list(std::shared_ptr<Page> page) {
        Result<T> res = Result::ok();
        res.data = page->getRecords();
        // create new page with values from input page
        res.page = std::make_shared<Page>();
        res.page->setCurrent(page->getCurrent());
        res.page->setSize(page->getSize());
        res.page->setTotal(page->getTotal());
        return res;
    }
    
    static Result<T> one(T obj, std::string message = "") {
        return one(StatusCode::OK, obj, message);
    }
    
    static Result<T> one(StatusCode code, T obj, std::string message) {
        Result<T> res = Result(code, message);
        res.data = std::make_shared<T>(obj);
        return res;
    }
    
    StatusCode getCode() const {
        return code;
    }
    
    void setCode(StatusCode c) {
        code = c;
    }
    
    std::string getMessage() const {
        return message;
    }
    
    void setMessage(std::string msg) {
        message = msg;
    }
    
    std::shared_ptr<Page> getPage() const {
        return page;
    }
    
    void setPage(std::shared_ptr<Page> p) {
        page = p;
    }
    
    std::shared_ptr<T> getData() const {
        return data;
    }
    
    void setData(T d) {
        data = std::make_shared<T>(d);
    }
    
private:
    StatusCode code;
    std::string message;
    std::shared_ptr<Page> page;
    std::shared_ptr<T> data;
};
