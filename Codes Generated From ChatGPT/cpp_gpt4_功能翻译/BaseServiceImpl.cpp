#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

class BaseDomain {
public:
    virtual ~BaseDomain() = default;
    virtual int getId() const = 0;
    virtual void setId(int id) = 0;
    virtual void save() = 0;
};

class BaseService {
protected:
    std::vector<BaseDomain*> entities;
public:
    virtual ~BaseService() = default;
    virtual BaseDomain* findById(int id) {
        auto it = std::find_if(entities.begin(), entities.end(), [&id](BaseDomain* obj) { return obj->getId() == id; });
        if (it != entities.end())
            return *it;
        else
            throw std::runtime_error("Entity not found");
    }
    virtual void save(BaseDomain* entity) {
        entity->save();
    }
    virtual void removeById(int id) {
        auto it = std::remove_if(entities.begin(), entities.end(), [&id](BaseDomain* obj) { return obj->getId() == id; });
        if (it != entities.end())
            entities.erase(it, entities.end());
        else
            throw std::runtime_error("Entity not found");
    }
};

class BaseDomainImpl : public BaseDomain {
private:
    int id;
public:
    BaseDomainImpl(int id) : id(id) {}
    int getId() const override { return id; }
    void setId(int id) override { this->id = id; }
    void save() override { std::cout << "Saving entity with id: " << id << std::endl; }
};

class BaseServiceImpl : public BaseService {
public:
    void addEntity(BaseDomain* entity) {
        entities.push_back(entity);
    }
    void removeEntity(BaseDomain* entity) {
        auto it = std::remove(entities.begin(), entities.end(), entity);
        if (it != entities.end())
            entities.erase(it, entities.end());
        else
            throw std::runtime_error("Entity not found");
    }
    BaseDomain* createEntity(int id) {
        BaseDomain* entity = new BaseDomainImpl(id);
        addEntity(entity);
        return entity;
    }
};

int main() {
    BaseServiceImpl service;
    BaseDomain* entity = service.createEntity(1);
    service.save(entity);
    BaseDomain* retrievedEntity = service.findById(1);
    service.removeById(1);
    try {
        service.findById(1);
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
