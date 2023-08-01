#include <iostream>
#include <type_traits>

template <typename T>
struct ClassWrapper {
    using type = T;
};

template <typename T>
class GenericBase {
public:
    using ValueType = T;
};

template <typename T>
class GenericDerived : public GenericBase<T> {
};

class ReflectionUtils {
public:
    template <typename T>
    static typename ClassWrapper<T>::type getGenericClass() {
        return typename ClassWrapper<T>::type();
    }

    template <typename T>
    static typename std::remove_pointer<decltype(std::declval<T>().getSuperClass())>::type getSuperClass() {
        return typename std::remove_pointer<decltype(std::declval<T>().getSuperClass())>::type();
    }

    template <typename T, size_t Index>
    static auto getSuperClassGenericType() -> typename std::tuple_element<Index, typename T::GenericTypeTuple>::type {
        return typename std::tuple_element<Index, typename T::GenericTypeTuple>::type();
    }
};

int main() {
    using Derived = GenericDerived<int>;

    auto genericClass = ReflectionUtils::getGenericClass<ClassWrapper<Derived::ValueType>>();
    std::cout << "Generic Class: " << typeid(genericClass).name() << std::endl;

    auto superClass = ReflectionUtils::getSuperClass<ClassWrapper<Derived>>();
    std::cout << "Super Class: " << typeid(superClass).name() << std::endl;

    auto superClassGenericType = ReflectionUtils::getSuperClassGenericType<Derived, 0>();
    std::cout << "Super Class Generic Type: " << typeid(superClassGenericType).name() << std::endl;

    return 0;
}
