#ifndef ECS_hpp
#define ECS_hpp

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

// Generate component id every time we create one
using ComponentID = std::size_t;

inline ComponentID getComponentTypeID() {
    static ComponentID lastID = 0;
    return lastID++;
}

// Template function to generate component IDs based on type T
template <typename T>
inline ComponentID getComponentTypeID() noexcept {
    static ComponentID typeID = getComponentTypeID();
    return typeID;
}

// constexpr evaluates this at compile time rather than run time
// Max amount of components an entity can hold
constexpr std::size_t maxComponents = 32;

// Setting aliases
using ComponentBitSet = std::bitset<maxComponents>;
// Array of pointers to components
using ComponentArray = std::array<Component*, maxComponents>;

class Component {
public:
    Entity* entity;
    
    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}
    
    virtual ~Component() {}
};

class Entity {
public:
    void update() {
        for(auto& c : components) c->update();
    }
    
    void draw() {
        for(auto& c : components) c->draw();
    }
    bool isActive() const { return active; }
    void destroy() { active = false; }
    
    template <typename T> bool hasComponent() const {
        // Returns whether or not a component is attached
        return componentBitSet[getComponentTypeID<T>];
    }
    
    template <typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs) {
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr{ c };
        components.emplace_back(std::move(uPtr));
        // This stores the pointer to the component in the 'componentArray'
        // at the index corresponding to its unique ID
        componentArray[getComponentTypeID<T>()] = c;
        // Sets the bit corresponding to the component type T to true
        // Indicating that the entity has this type of component
        componentBitSet[getComponentTypeID()] = true;
        
        c->init();
        
        return *c;
    }
    
    template <typename T> T& getComponent() const {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        // Dereferences *T to get type T
        return *static_cast<T*>(ptr);
    }
    
private:
    bool active = true;
    // vectors are arrays of variable size
    // These vectors are of type unique pointers to components
    std::vector<std::unique_ptr<Component>> components;
    
    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
};

class Manager {
public:
    void update() {
        for (auto& e : entities) {
            e->update();
        }
    }
    
    void draw() {
        for (auto& e : entities) {
            e->draw();
        }
    }

    void refresh() {
        // Removes entities that are no longer active
        entities.erase(
            std::remove_if(
                std::begin(entities), // Start of the range
                std::end(entities), // End of the range
                [](const std::unique_ptr<Entity> &mEntity) { // Lambda function to check each entity
                    // Returns true if the entity is not active, signalling the remove_if to remove the entity
                    return !mEntity->isActive(); // Returns true if the entity is not active
                    
                }
            ),
            std::end(entities) // Erase elements from the end of the range
        );
    }
    
    Entity& addEntity() {
        Entity* e = new Entity();
        std::unique_ptr<Entity> uPtr{ e };
        entities.emplace_back(std::move(uPtr));
        
        return *e;
    }
    
private:
    // vector of unique ptrs to entities
    std::vector<std::unique_ptr<Entity>> entities;
    

};

#endif
