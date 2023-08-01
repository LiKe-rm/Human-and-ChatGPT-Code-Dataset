#include <unordered_map>
#include <string>
#include <iostream>
#include <stdexcept>

class BaseEntity {
public:
    virtual ~BaseEntity() = default;
    virtual long getId() const = 0;
    virtual void setId(long id) = 0;
};

class BaseShopEntity : public BaseEntity {
private:
    long id;
public:
    BaseShopEntity(long id) : id(id) {}
    long getId() const override { return id; }
    void setId(long id) override { this->id = id; }
};

class BaseService {
protected:
    std::unordered_map<long, BaseShopEntity> entities;
public:
    virtual ~BaseService() = default;
    virtual long count() const {
        return entities.size();
    }
    virtual void addEntity(const BaseShopEntity& entity) {
        entities[entity.getId()] = entity;
    }
    virtual void removeEntity(long id) {
        entities.erase(id);
    }
};

class BaseShopController {
private:
    BaseService* baseService;
public:
    BaseShopController(BaseService* baseService) : baseService(baseService) {}
    void checkUnique(long id, const std::string& name, const std::string& column, const std::string& value) {
        if (baseService->count() > 0) {
            throw std::runtime_error(name + " already exists");
        }
    }
    long findCount(long id, const std::string& column, const std::string& value) {
        // This is a simple placeholder as column and value aren't used in this sample
        // In a real-world application, you would use these to filter the entities
        return baseService->count();
    }
};

int main() {
    BaseService baseService;
    BaseShopController controller(&baseService);
    try {
        controller.checkUnique(1, "Test", "Column", "Value");
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    BaseShopEntity entity(1);
    baseService.addEntity(entity);
    try {
        controller.checkUnique(1, "Test", "Column", "Value");
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
