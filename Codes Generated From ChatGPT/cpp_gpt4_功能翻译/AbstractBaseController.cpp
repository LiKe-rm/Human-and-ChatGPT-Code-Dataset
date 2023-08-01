#include <ctime>
#include <vector>
#include <iostream>
#include <memory>

template<typename T>
class BaseEntity {
public:
    virtual ~BaseEntity() = default;
    virtual T getId() = 0;
    virtual void setId(T id) = 0;
    virtual void setUpdatedAt(time_t updatedAt) = 0;
    virtual void setCreatedAt(time_t createdAt) = 0;
};

class Query {
public:
    Query(const std::string& body) {}
    void eq(const std::string& id, long value) {}
};

template<typename T>
class BaseService {
public:
    virtual ~BaseService() = default;
    virtual std::unique_ptr<BaseEntity<T>> findById(T id) = 0;
    virtual void beforeSave(BaseEntity<T>* entity) = 0;
    virtual void save(BaseEntity<T>* entity) = 0;
    virtual void updateById(BaseEntity<T>* entity) = 0;
    virtual bool removeById(T id) = 0;
    virtual void saveManyToMany(BaseEntity<T>* entity) = 0;
};

class QueryRequest {};
class QueryParser {
public:
    QueryParser() {}
    QueryRequest parseQueryRequest(const std::string& clazz, const std::string& body) {
        return QueryRequest();
    }
};

template<typename T>
class AbstractBaseController {
public:
    AbstractBaseController() = default;
    explicit AbstractBaseController(std::unique_ptr<BaseService<T>> baseService)
        : baseService(std::move(baseService)) {}
    BaseService<T>* getBaseService() {
        return baseService.get();
    }
    QueryRequest createRequest(const std::string& body, const std::string& clazz) {
        QueryParser parser;
        return parser.parseQueryRequest(clazz, body);
    }
    BaseEntity<T>* getEntity(long id) {
        return baseService->findById(id);
    }
    BaseEntity<T>* getEntity(long id, const std::string& body) {
        Query query(body);
        query.eq("id", id);
        return baseService->findById(id);
    }
    BaseEntity<T>* createEntity(BaseEntity<T>* dto) {
        baseService->beforeSave(dto);
        baseService->save(dto);
        baseService->saveManyToMany(dto);
        return dto;
    }
    BaseEntity<T>* updateEntity(T id, BaseEntity<T>* dto) {
        baseService->beforeSave(dto);
        auto domain = baseService->findById(dto->getId());
        if (!domain) {
            throw std::runtime_error("Entity not found");
        }
        dto->setUpdatedAt(time(nullptr));
        baseService->updateById(dto);
        baseService->saveManyToMany(dto);
        return dto;
    }
    bool deleteEntity(T id) {
        auto domain = baseService->findById(id);
        if (!domain) {
            return true;
        }
        return baseService->removeById(id);
    }

private:
    std::unique_ptr<BaseService<T>> baseService;
};
