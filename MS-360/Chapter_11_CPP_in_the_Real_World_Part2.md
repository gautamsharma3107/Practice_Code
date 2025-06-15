# Chapter 11: C++ in the Real World (Part 2)

## 11.2 C++ in Game Engines

Game engines are complex software frameworks that provide developers with the necessary tools to create video games efficiently. They handle core functionalities such as rendering, physics, audio, collision detection, artificial intelligence, and more. C++ has been the dominant programming language in the game industry for decades, powering most commercial game engines due to its unique combination of performance, control, and abstraction capabilities.

### 11.2.1 Why C++ Dominates Game Development

C++ offers several key advantages that make it ideal for game engine development:

#### 1. Performance

Games need to process enormous amounts of data in real-time while maintaining high frame rates (typically 30-60+ frames per second):
- **Low-level optimizations**: Direct memory management allows for cache-friendly data layouts
- **Minimal runtime overhead**: No garbage collection pauses or interpreter overhead
- **Compiled code efficiency**: Modern C++ compilers produce highly optimized machine code
- **SIMD instruction support**: Explicit vectorization for parallel data processing

#### 2. Hardware Control

C++ provides granular control over hardware resources:
- **Direct memory management**: Essential for managing limited console memory
- **Hardware acceleration**: Direct access to GPU APIs (DirectX, Vulkan, OpenGL)
- **Platform-specific optimizations**: Ability to target specific hardware features
- **Memory layout control**: Precise data alignment for performance-critical operations

#### 3. Object-Oriented Design with Performance

C++ offers a balanced approach to code organization:
- **Classes and inheritance**: For organizing complex engine subsystems
- **Templates**: For type-safe generic programming without runtime overhead
- **Polymorphism when needed**: Virtual functions for extensible systems
- **RAII pattern**: Resource management tied to object lifecycles

#### 4. Modern Features with Backward Compatibility

Modern C++ (C++11 onward) has added numerous features that benefit game development:
- **Smart pointers**: Safer memory management without garbage collection
- **Move semantics**: Efficient resource transfer without deep copying
- **Lambda expressions**: Concise callback implementations
- **Variadic templates**: Type-safe heterogeneous containers

### 11.2.2 Core Components of Game Engines in C++

#### 1. Rendering Engine

The rendering engine is responsible for drawing graphics on screen, typically implemented using a combination of C++ and shader languages (HLSL, GLSL):

```cpp
class RenderingEngine {
private:
    std::vector<RenderableObject*> renderQueue;
    Camera* activeCamera;
    LightManager lightManager;
    
    // Renderer state
    ShaderProgram* activeShader;
    RenderTarget* activeTarget;
    
public:
    void initialize() {
        // Initialize graphics API (DirectX, OpenGL, Vulkan, etc.)
        GraphicsAPI::initialize();
        
        // Create default resources
        ResourceManager::loadDefaultShaders();
    }
    
    void setActiveCamera(Camera* camera) {
        activeCamera = camera;
    }
    
    void submitForRendering(RenderableObject* object) {
        // Add object to render queue
        renderQueue.push_back(object);
    }
    
    void render() {
        // Sort objects by material/shader for rendering efficiency
        std::sort(renderQueue.begin(), renderQueue.end(), 
                 [](const RenderableObject* a, const RenderableObject* b) {
                     return a->getMaterial()->getShaderID() < b->getMaterial()->getShaderID();
                 });
        
        // Set up view and projection matrices from camera
        Matrix4x4 viewMatrix = activeCamera->getViewMatrix();
        Matrix4x4 projectionMatrix = activeCamera->getProjectionMatrix();
        
        // Current shader for state tracking
        unsigned int currentShaderId = 0;
        
        // Render each object
        for (RenderableObject* object : renderQueue) {
            // Skip objects outside the camera frustum
            if (!activeCamera->isVisible(object->getBoundingBox())) {
                continue;
            }
            
            // Set shader if different from current
            unsigned int objectShaderId = object->getMaterial()->getShaderID();
            if (objectShaderId != currentShaderId) {
                ShaderProgram* shader = ResourceManager::getShader(objectShaderId);
                shader->bind();
                
                // Set camera-related uniforms
                shader->setUniformMatrix4("viewMatrix", viewMatrix);
                shader->setUniformMatrix4("projectionMatrix", projectionMatrix);
                
                // Set global lighting parameters
                lightManager.setLightUniforms(shader);
                
                currentShaderId = objectShaderId;
                activeShader = shader;
            }
            
            // Set object-specific uniforms
            activeShader->setUniformMatrix4("modelMatrix", object->getTransformMatrix());
            
            // Bind material textures
            object->getMaterial()->bind(activeShader);
            
            // Draw the mesh
            object->getMesh()->draw();
        }
        
        // Clear render queue for next frame
        renderQueue.clear();
    }
};
```

#### 2. Physics Engine

The physics engine simulates physical interactions between game objects:

```cpp
class PhysicsEngine {
private:
    std::vector<RigidBody*> bodies;
    std::vector<Collider*> colliders;
    Vector3 gravity;
    float fixedTimestep;
    
    // Spatial partitioning for efficient collision detection
    OctTree spatialPartitioning;
    
public:
    PhysicsEngine() : gravity(0, -9.81f, 0), fixedTimestep(1.0f/60.0f) {}
    
    void setGravity(const Vector3& g) {
        gravity = g;
    }
    
    void addRigidBody(RigidBody* body) {
        bodies.push_back(body);
        
        // Add collider to spatial partitioning
        if (body->getCollider()) {
            spatialPartitioning.insert(body->getCollider());
            colliders.push_back(body->getCollider());
        }
    }
    
    void removeRigidBody(RigidBody* body) {
        // Remove from rigid bodies list
        auto it = std::find(bodies.begin(), bodies.end(), body);
        if (it != bodies.end()) {
            bodies.erase(it);
        }
        
        // Remove collider from spatial partitioning
        if (body->getCollider()) {
            spatialPartitioning.remove(body->getCollider());
            
            // Remove from colliders list
            auto colliderIt = std::find(colliders.begin(), colliders.end(), body->getCollider());
            if (colliderIt != colliders.end()) {
                colliders.erase(colliderIt);
            }
        }
    }
    
    void update(float deltaTime) {
        // Use fixed timestep for stable physics
        static float accumulator = 0.0f;
        accumulator += deltaTime;
        
        while (accumulator >= fixedTimestep) {
            updatePhysics(fixedTimestep);
            accumulator -= fixedTimestep;
        }
    }
    
private:
    void updatePhysics(float dt) {
        // Apply forces to all bodies
        for (RigidBody* body : bodies) {
            if (!body->isStatic()) {
                // Apply gravity
                body->applyForce(gravity * body->getMass());
                
                // Update velocity
                Vector3 acceleration = body->getAccumulatedForce() * body->getInverseMass();
                body->setVelocity(body->getVelocity() + acceleration * dt);
                
                // Apply damping
                body->setVelocity(body->getVelocity() * (1.0f - body->getDamping() * dt));
                
                // Reset accumulated force
                body->clearAccumulatedForce();
            }
        }
        
        // Detect collisions
        std::vector<CollisionPair> collisions = detectCollisions();
        
        // Resolve collisions
        resolveCollisions(collisions, dt);
        
        // Update positions
        for (RigidBody* body : bodies) {
            if (!body->isStatic()) {
                // Update position based on velocity
                body->setPosition(body->getPosition() + body->getVelocity() * dt);
            }
        }
        
        // Update spatial partitioning
        updateSpatialPartitioning();
    }
    
    std::vector<CollisionPair> detectCollisions() {
        std::vector<CollisionPair> collisions;
        
        // Broad phase: use spatial partitioning to find potential collisions
        for (Collider* colliderA : colliders) {
            // Query spatial partitioning for potential collisions
            std::vector<Collider*> potentialCollisions = 
                spatialPartitioning.query(colliderA->getBoundingBox());
            
            // Narrow phase: detailed collision checks
            for (Collider* colliderB : potentialCollisions) {
                // Skip self-collision
                if (colliderA == colliderB) continue;
                
                // Perform detailed collision detection
                CollisionInfo info;
                if (checkCollision(colliderA, colliderB, info)) {
                    collisions.push_back({colliderA->getRigidBody(), colliderB->getRigidBody(), info});
                }
            }
        }
        
        return collisions;
    }
    
    void resolveCollisions(const std::vector<CollisionPair>& collisions, float dt) {
        for (const CollisionPair& collision : collisions) {
            RigidBody* bodyA = collision.bodyA;
            RigidBody* bodyB = collision.bodyB;
            
            // Skip if both are static
            if (bodyA->isStatic() && bodyB->isStatic()) continue;
            
            // Calculate relative velocity
            Vector3 relativeVelocity = bodyB->getVelocity() - bodyA->getVelocity();
            
            // Calculate impulse magnitude
            float inverseMassSum = bodyA->getInverseMass() + bodyB->getInverseMass();
            if (inverseMassSum == 0.0f) continue; // Both bodies have infinite mass
            
            float velAlongNormal = relativeVelocity.dot(collision.info.normal);
            
            // Don't resolve if objects are separating
            if (velAlongNormal > 0) continue;
            
            // Calculate coefficient of restitution (bounciness)
            float e = std::min(bodyA->getRestitution(), bodyB->getRestitution());
            
            // Calculate impulse scalar
            float j = -(1.0f + e) * velAlongNormal / inverseMassSum;
            
            // Apply impulse
            Vector3 impulse = collision.info.normal * j;
            bodyA->applyImpulse(-impulse);
            bodyB->applyImpulse(impulse);
            
            // Apply positional correction to prevent sinking
            float percent = 0.2f; // Penetration percentage to correct
            float slop = 0.01f; // Penetration allowance
            Vector3 correction = collision.info.normal * 
                                (std::max(collision.info.penetrationDepth - slop, 0.0f) * 
                                percent / inverseMassSum);
            
            bodyA->setPosition(bodyA->getPosition() - correction * bodyA->getInverseMass());
            bodyB->setPosition(bodyB->getPosition() + correction * bodyB->getInverseMass());
        }
    }
    
    void updateSpatialPartitioning() {
        // Update the spatial partitioning structure with new object positions
        spatialPartitioning.clear();
        for (Collider* collider : colliders) {
            spatialPartitioning.insert(collider);
        }
    }
};
```

#### 3. Entity Component System (ECS)

Modern game engines often use an ECS architecture for organizing game objects:

```cpp
// Component base class
class Component {
public:
    virtual ~Component() = default;
    virtual void initialize() {}
    virtual void update(float deltaTime) {}
    
    Entity* getEntity() const { return entity; }
    
protected:
    Entity* entity = nullptr;
    friend class Entity;
};

// Transform component
class TransformComponent : public Component {
private:
    Vector3 position;
    Quaternion rotation;
    Vector3 scale;
    
public:
    TransformComponent() : position(0, 0, 0), rotation(), scale(1, 1, 1) {}
    
    // Getters and setters
    void setPosition(const Vector3& pos) { position = pos; }
    Vector3 getPosition() const { return position; }
    
    void setRotation(const Quaternion& rot) { rotation = rot; }
    Quaternion getRotation() const { return rotation; }
    
    void setScale(const Vector3& s) { scale = s; }
    Vector3 getScale() const { return scale; }
    
    // Generate transformation matrix
    Matrix4x4 getTransformMatrix() const {
        return Matrix4x4::createTransformation(position, rotation, scale);
    }
};

// Render component
class RenderComponent : public Component {
private:
    Mesh* mesh;
    Material* material;
    bool castsShadow;
    
public:
    RenderComponent() : mesh(nullptr), material(nullptr), castsShadow(true) {}
    
    void initialize() override {
        // Register with rendering system
        RenderingSystem::getInstance().registerRenderable(this);
    }
    
    void setMesh(Mesh* m) { mesh = m; }
    Mesh* getMesh() const { return mesh; }
    
    void setMaterial(Material* mat) { material = mat; }
    Material* getMaterial() const { return material; }
    
    void setCastsShadow(bool cast) { castsShadow = cast; }
    bool getCastsShadow() const { return castsShadow; }
};

// Entity class
class Entity {
private:
    std::string name;
    bool active;
    std::vector<std::unique_ptr<Component>> components;
    
public:
    Entity(const std::string& entityName = "Entity") : name(entityName), active(true) {}
    
    template <typename T, typename... Args>
    T* addComponent(Args&&... args) {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
        
        // Check if component already exists
        T* existingComponent = getComponent<T>();
        if (existingComponent) {
            return existingComponent;
        }
        
        // Create component
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        component->entity = this;
        
        T* componentPtr = component.get();
        components.push_back(std::move(component));
        
        // Initialize the component
        componentPtr->initialize();
        
        return componentPtr;
    }
    
    template <typename T>
    T* getComponent() const {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
        
        for (const auto& component : components) {
            if (auto casted = dynamic_cast<T*>(component.get())) {
                return casted;
            }
        }
        
        return nullptr;
    }
    
    void update(float deltaTime) {
        if (!active) return;
        
        for (auto& component : components) {
            component->update(deltaTime);
        }
    }
    
    const std::string& getName() const { return name; }
    void setName(const std::string& newName) { name = newName; }
    
    bool isActive() const { return active; }
    void setActive(bool isActive) { active = isActive; }
};

// Scene class to manage entities
class Scene {
private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::string name;
    
public:
    Scene(const std::string& sceneName = "Scene") : name(sceneName) {}
    
    Entity* createEntity(const std::string& name = "Entity") {
        auto entity = std::make_unique<Entity>(name);
        Entity* entityPtr = entity.get();
        entities.push_back(std::move(entity));
        return entityPtr;
    }
    
    void update(float deltaTime) {
        for (auto& entity : entities) {
            entity->update(deltaTime);
        }
    }
    
    void removeEntity(Entity* entity) {
        auto it = std::find_if(entities.begin(), entities.end(),
                              [entity](const std::unique_ptr<Entity>& e) {
                                  return e.get() == entity;
                              });
        
        if (it != entities.end()) {
            entities.erase(it);
        }
    }
    
    std::vector<Entity*> findEntitiesByName(const std::string& name) {
        std::vector<Entity*> result;
        
        for (auto& entity : entities) {
            if (entity->getName() == name) {
                result.push_back(entity.get());
            }
        }
        
        return result;
    }
};
```

#### 4. Input System

The input system handles player interactions with the game:

```cpp
// Input action types
enum class InputActionType {
    Pressed,
    Released,
    Held
};

// Input action mapping
struct InputAction {
    std::string name;
    InputActionType type;
    int keyCode;
    std::function<void()> callback;
};

// Input system class
class InputSystem {
private:
    // Key state tracking
    std::unordered_map<int, bool> currentKeyStates;
    std::unordered_map<int, bool> previousKeyStates;
    
    // Input action mappings
    std::vector<InputAction> actions;
    
    // Mouse position
    Vector2 mousePosition;
    Vector2 previousMousePosition;
    Vector2 mouseDelta;
    
    // Singleton instance
    static InputSystem* instance;
    
public:
    // Get singleton instance
    static InputSystem& getInstance() {
        if (!instance) {
            instance = new InputSystem();
        }
        return *instance;
    }
    
    void initialize() {
        // Platform-specific initialization
    }
    
    void update() {
        // Update previous key states
        previousKeyStates = currentKeyStates;
        
        // Update previous mouse position
        previousMousePosition = mousePosition;
        
        // Platform-specific input polling
        pollPlatformInput();
        
        // Calculate mouse delta
        mouseDelta = mousePosition - previousMousePosition;
        
        // Process input actions
        for (const InputAction& action : actions) {
            int keyCode = action.keyCode;
            
            switch (action.type) {
                case InputActionType::Pressed:
                    if (isKeyPressed(keyCode) && action.callback) {
                        action.callback();
                    }
                    break;
                    
                case InputActionType::Released:
                    if (isKeyReleased(keyCode) && action.callback) {
                        action.callback();
                    }
                    break;
                    
                case InputActionType::Held:
                    if (isKeyDown(keyCode) && action.callback) {
                        action.callback();
                    }
                    break;
            }
        }
    }
    
    // Register an input action
    void registerAction(const std::string& name, InputActionType type, int keyCode, std::function<void()> callback) {
        actions.push_back({name, type, keyCode, callback});
    }
    
    // Key state checking methods
    bool isKeyDown(int keyCode) const {
        auto it = currentKeyStates.find(keyCode);
        return (it != currentKeyStates.end()) ? it->second : false;
    }
    
    bool isKeyPressed(int keyCode) const {
        bool current = isKeyDown(keyCode);
        
        auto it = previousKeyStates.find(keyCode);
        bool previous = (it != previousKeyStates.end()) ? it->second : false;
        
        return current && !previous;
    }
    
    bool isKeyReleased(int keyCode) const {
        bool current = isKeyDown(keyCode);
        
        auto it = previousKeyStates.find(keyCode);
        bool previous = (it != previousKeyStates.end()) ? it->second : false;
        
        return !current && previous;
    }
    
    // Mouse methods
    Vector2 getMousePosition() const { return mousePosition; }
    Vector2 getMouseDelta() const { return mouseDelta; }
    
private:
    InputSystem() {}
    
    void pollPlatformInput() {
        // Platform-specific input polling code
        // For example, using GLFW, SDL, Win32, etc.
        
        // This would update currentKeyStates and mousePosition
    }
};
```

### 11.2.3 Memory Management in Game Engines

Game engines require specialized memory management for performance and stability:

```cpp
// Custom allocator for game objects
class GameObjectAllocator {
private:
    struct MemoryChunk {
        void* memory;
        size_t size;
        size_t used;
        MemoryChunk* next;
    };
    
    MemoryChunk* firstChunk;
    size_t chunkSize;
    
    // Memory tracking
    size_t totalAllocated;
    size_t totalUsed;
    int numAllocations;
    
public:
    GameObjectAllocator(size_t defaultChunkSize = 1024 * 1024) // 1MB default
        : firstChunk(nullptr), chunkSize(defaultChunkSize),
          totalAllocated(0), totalUsed(0), numAllocations(0) {}
    
    ~GameObjectAllocator() {
        // Free all allocated memory
        MemoryChunk* current = firstChunk;
        while (current) {
            MemoryChunk* next = current->next;
            free(current->memory);
            free(current);
            current = next;
        }
    }
    
    // Allocate memory from the pool
    void* allocate(size_t size, size_t alignment = 16) {
        size_t alignmentMask = alignment - 1;
        size_t headerSize = sizeof(AllocationHeader);
        
        // Find a chunk with enough space
        MemoryChunk* chunk = findChunkWithSpace(size + headerSize + alignment);
        if (!chunk) {
            // Create a new chunk if none has enough space
            size_t newChunkSize = std::max(chunkSize, size + headerSize + alignment);
            chunk = createChunk(newChunkSize);
        }
        
        // Calculate aligned address
        uintptr_t baseAddress = reinterpret_cast<uintptr_t>(chunk->memory) + chunk->used;
        uintptr_t alignedAddress = (baseAddress + headerSize + alignmentMask) & ~alignmentMask;
        
        // Calculate adjustment
        size_t adjustment = alignedAddress - (baseAddress + headerSize);
        
        // Store allocation header before the aligned memory
        AllocationHeader* header = reinterpret_cast<AllocationHeader*>(alignedAddress - headerSize);
        header->size = size;
        header->adjustment = adjustment;
        
        // Update chunk usage
        chunk->used += size + headerSize + adjustment;
        
        // Update statistics
        totalUsed += size + headerSize + adjustment;
        numAllocations++;
        
        // Return aligned address
        return reinterpret_cast<void*>(alignedAddress);
    }
    
    // Free memory
    void deallocate(void* ptr) {
        if (!ptr) return;
        
        // Get header
        AllocationHeader* header = reinterpret_cast<AllocationHeader*>(
            reinterpret_cast<uintptr_t>(ptr) - sizeof(AllocationHeader));
        
        // In a real pool allocator, we might not actually free anything here,
        // but we can update statistics
        totalUsed -= header->size + sizeof(AllocationHeader) + header->adjustment;
        numAllocations--;
    }
    
    // Reset the allocator (for level transitions, etc.)
    void reset() {
        MemoryChunk* chunk = firstChunk;
        while (chunk) {
            chunk->used = 0;
            chunk = chunk->next;
        }
        
        totalUsed = 0;
        numAllocations = 0;
    }
    
    // Statistics
    size_t getTotalAllocated() const { return totalAllocated; }
    size_t getTotalUsed() const { return totalUsed; }
    int getNumAllocations() const { return numAllocations; }
    
private:
    struct AllocationHeader {
        size_t size;
        size_t adjustment;
    };
    
    MemoryChunk* findChunkWithSpace(size_t size) {
        MemoryChunk* chunk = firstChunk;
        while (chunk) {
            if (chunk->size - chunk->used >= size) {
                return chunk;
            }
            chunk = chunk->next;
        }
        return nullptr;
    }
    
    MemoryChunk* createChunk(size_t size) {
        // Allocate chunk header
        MemoryChunk* chunk = static_cast<MemoryChunk*>(malloc(sizeof(MemoryChunk)));
        
        // Allocate chunk memory
        chunk->memory = malloc(size);
        chunk->size = size;
        chunk->used = 0;
        
        // Add to linked list
        chunk->next = firstChunk;
        firstChunk = chunk;
        
        // Update statistics
        totalAllocated += size;
        
        return chunk;
    }
};

// Custom allocator for game objects
class GameObjectAllocator {
private:
    struct MemoryChunk {
        void* memory;
        size_t size;
        size_t used;
        MemoryChunk* next;
    };
    
    MemoryChunk* firstChunk;
    size_t chunkSize;
    
    // Memory tracking
    size_t totalAllocated;
    size_t totalUsed;
    int numAllocations;
    
public:
    GameObjectAllocator(size_t defaultChunkSize = 1024 * 1024) // 1MB default
        : firstChunk(nullptr), chunkSize(defaultChunkSize),
          totalAllocated(0), totalUsed(0), numAllocations(0) {}
    
    ~GameObjectAllocator() {
        // Free all allocated memory
        MemoryChunk* current = firstChunk;
        while (current) {
            MemoryChunk* next = current->next;
            free(current->memory);
            free(current);
            current = next;
        }
    }
    
    // Allocate memory from the pool
    void* allocate(size_t size, size_t alignment = 16) {
        size_t alignmentMask = alignment - 1;
        size_t headerSize = sizeof(AllocationHeader);
        
        // Find a chunk with enough space
        MemoryChunk* chunk = findChunkWithSpace(size + headerSize + alignment);
        if (!chunk) {
            // Create a new chunk if none has enough space
            size_t newChunkSize = std::max(chunkSize, size + headerSize + alignment);
            chunk = createChunk(newChunkSize);
        }
        
        // Calculate aligned address
        uintptr_t baseAddress = reinterpret_cast<uintptr_t>(chunk->memory) + chunk->used;
        uintptr_t alignedAddress = (baseAddress + headerSize + alignmentMask) & ~alignmentMask;
        
        // Calculate adjustment
        size_t adjustment = alignedAddress - (baseAddress + headerSize);
        
        // Store allocation header before the aligned memory
        AllocationHeader* header = reinterpret_cast<AllocationHeader*>(alignedAddress - headerSize);
        header->size = size;
        header->adjustment = adjustment;
        
        // Update chunk usage
        chunk->used += size + headerSize + adjustment;
        
        // Update statistics
        totalUsed += size + headerSize + adjustment;
        numAllocations++;
        
        // Return aligned address
        return reinterpret_cast<void*>(alignedAddress);
    }
    
    // Free memory
    void deallocate(void* ptr) {
        if (!ptr) return;
        
        // Get header
        AllocationHeader* header = reinterpret_cast<AllocationHeader*>(
            reinterpret_cast<uintptr_t>(ptr) - sizeof(AllocationHeader));
        
        // In a real pool allocator, we might not actually free anything here,
        // but we can update statistics
        totalUsed -= header->size + sizeof(AllocationHeader) + header->adjustment;
        numAllocations--;
    }
    
    // Reset the allocator (for level transitions, etc.)
    void reset() {
        MemoryChunk* chunk = firstChunk;
        while (chunk) {
            chunk->used = 0;
            chunk = chunk->next;
        }
        
        totalUsed = 0;
        numAllocations = 0;
    }
    
    // Statistics
    size_t getTotalAllocated() const { return totalAllocated; }
    size_t getTotalUsed() const { return totalUsed; }
    int getNumAllocations() const { return numAllocations; }
    
private:
    struct AllocationHeader {
        size_t size;
        size_t adjustment;
    };
    
    MemoryChunk* findChunkWithSpace(size_t size) {
        MemoryChunk* chunk = firstChunk;
        while (chunk) {
            if (chunk->size - chunk->used >= size) {
                return chunk;
            }
            chunk = chunk->next;
        }
        return nullptr;
    }
    
    MemoryChunk* createChunk(size_t size) {
        // Allocate chunk header
        MemoryChunk* chunk = static_cast<MemoryChunk*>(malloc(sizeof(MemoryChunk)));
        
        // Allocate chunk memory
        chunk->memory = malloc(size);
        chunk->size = size;
        chunk->used = 0;
        
        // Add to linked list
        chunk->next = firstChunk;
        firstChunk = chunk;
        
        // Update statistics
        totalAllocated += size;
        
        return chunk;
    }
};
```

### 11.2.4 Data-Oriented Design in Game Engines

Modern game engines often employ data-oriented design for better cache utilization:

```cpp
// Traditional object-oriented approach
class GameObject {
private:
    Vector3 position;
    Quaternion rotation;
    Vector3 scale;
    Mesh* mesh;
    Material* material;
    PhysicsBody* physicsBody;
    
public:
    void update(float deltaTime) {
        // Update logic
        if (physicsBody) {
            position = physicsBody->getPosition();
            rotation = physicsBody->getRotation();
        }
    }
    
    void render() {
        if (mesh && material) {
            // Set transform
            Matrix4x4 transform = Matrix4x4::createTransformMatrix(position, rotation, scale);
            
            // Render the mesh
            material->bind();
            mesh->draw(transform);
        }
    }
};

// Data-oriented approach
class GameObjectSystem {
private:
    // Components stored in structure-of-arrays for better cache coherency
    struct {
        std::vector<Vector3> positions;
        std::vector<Quaternion> rotations;
        std::vector<Vector3> scales;
    } transforms;
    
    struct {
        std::vector<Mesh*> meshes;
        std::vector<Material*> materials;
    } renderers;
    
    struct {
        std::vector<PhysicsBody*> bodies;
        std::vector<bool> hasPhysics;  // Flag for whether an entity has physics
    } physics;
    
    std::vector<bool> active;  // Active status for each entity
    int entityCount = 0;
    
public:
    int createEntity() {
        int entityId = entityCount++;
        
        // Add default component values
        transforms.positions.push_back(Vector3(0, 0, 0));
        transforms.rotations.push_back(Quaternion());
        transforms.scales.push_back(Vector3(1, 1, 1));
        
        renderers.meshes.push_back(nullptr);
        renderers.materials.push_back(nullptr);
        
        physics.bodies.push_back(nullptr);
        physics.hasPhysics.push_back(false);
        
        active.push_back(true);
        
        return entityId;
    }
    
    void destroyEntity(int entityId) {
        // In a real engine, we'd need more sophisticated removal
        // This is a simplified version
        if (entityId >= 0 && entityId < entityCount) {
            active[entityId] = false;
        }
    }
    
    void setTransform(int entityId, const Vector3& position, const Quaternion& rotation, const Vector3& scale) {
        if (entityId >= 0 && entityId < entityCount) {
            transforms.positions[entityId] = position;
            transforms.rotations[entityId] = rotation;
            transforms.scales[entityId] = scale;
        }
    }
    
    void setRenderer(int entityId, Mesh* mesh, Material* material) {
        if (entityId >= 0 && entityId < entityCount) {
            renderers.meshes[entityId] = mesh;
            renderers.materials[entityId] = material;
        }
    }
    
    void setPhysics(int entityId, PhysicsBody* body) {
        if (entityId >= 0 && entityId < entityCount) {
            physics.bodies[entityId] = body;
            physics.hasPhysics[entityId] = (body != nullptr);
        }
    }
    
    void updatePhysics(float deltaTime) {
        // Update physics in batch
        for (int i = 0; i < entityCount; ++i) {
            if (!active[i] || !physics.hasPhysics[i]) continue;
            
            PhysicsBody* body = physics.bodies[i];
            if (body) {
                // Update transform from physics
                transforms.positions[i] = body->getPosition();
                transforms.rotations[i] = body->getRotation();
            }
        }
    }
    
    void render(RenderContext& context) {
        // Sort by material for efficient rendering
        std::vector<int> renderOrder;
        for (int i = 0; i < entityCount; ++i) {
            if (active[i] && renderers.meshes[i] && renderers.materials[i]) {
                renderOrder.push_back(i);
            }
        }
        
        // Sort by material to minimize state changes
        std::sort(renderOrder.begin(), renderOrder.end(),
                 [this](int a, int b) {
                     return renderers.materials[a] < renderers.materials[b];
                 });
        
        // Render in optimized order
        Material* currentMaterial = nullptr;
        
        for (int idx : renderOrder) {
            // Apply material only when it changes
            if (renderers.materials[idx] != currentMaterial) {
                if (currentMaterial) {
                    currentMaterial->unbind();
                }
                
                currentMaterial = renderers.materials[idx];
                currentMaterial->bind();
            }
            
            // Create transform matrix
            Matrix4x4 transform = Matrix4x4::createTransformMatrix(
                transforms.positions[idx],
                transforms.rotations[idx],
                transforms.scales[idx]
            );
            
            // Set transform uniform
            context.setModelMatrix(transform);
            
            // Draw mesh
            renderers.meshes[idx]->draw();
        }
        
        // Unbind last material
        if (currentMaterial) {
            currentMaterial->unbind();
        }
    }
};
```

### 11.2.5 Multithreading in Game Engines

Modern game engines utilize multiple threads for better performance:

```cpp
class GameEngine {
private:
    bool running = false;
    
    // Thread synchronization
    std::atomic<bool> renderingCompleted = true;
    std::atomic<bool> physicsCompleted = true;
    std::mutex gameStateMutex;
    
    // Game state
    Scene* activeScene;
    float deltaTime;
    
    // Threads
    std::thread renderThread;
    std::thread physicsThread;
    std::thread audioThread;
    
public:
    void initialize() {
        // Initialize systems
        renderingSystem.initialize();
        physicsSystem.initialize();
        inputSystem.initialize();
        audioSystem.initialize();
        
        // Load initial scene
        activeScene = loadScene("MainMenu");
    }
    
    void run() {
        running = true;
        
        // Start worker threads
        renderThread = std::thread(&GameEngine::renderThreadFunc, this);
        physicsThread = std::thread(&GameEngine::physicsThreadFunc, this);
        audioThread = std::thread(&GameEngine::audioThreadFunc, this);
        
        // Main thread handles game logic and input
        mainThreadFunc();
        
        // Wait for worker threads to finish
        renderThread.join();
        physicsThread.join();
        audioThread.join();
    }
    
    void stop() {
        running = false;
    }
    
private:
    void mainThreadFunc() {
        Timer timer;
        
        while (running) {
            // Calculate delta time
            deltaTime = timer.getElapsedAndReset();
            
            // Process input
            inputSystem.update();
            
            // Process game logic
            {
                std::lock_guard<std::mutex> lock(gameStateMutex);
                
                if (activeScene) {
                    activeScene->update(deltaTime);
                }
                
                // Wait for physics to complete before doing next update
                while (!physicsCompleted.load() && running) {
                    std::this_thread::yield();
                }
                
                // Reset physics flag for next frame
                physicsCompleted.store(false);
            }
            
            // Cap frame rate if needed
            limitFrameRate(60);
        }
    }
    
    void renderThreadFunc() {
        while (running) {
            // Check if ready to render
            if (activeScene) {
                {
                    // Access scene data
                    std::lock_guard<std::mutex> lock(gameStateMutex);
                    
                    // Set up camera
                    Camera* mainCamera = activeScene->getMainCamera();
                    renderingSystem.setActiveCamera(mainCamera);
                    
                    // Submit objects for rendering
                    std::vector<Entity*> entities = activeScene->getEntities();
                    for (Entity* entity : entities) {
                        RenderComponent* renderer = entity->getComponent<RenderComponent>();
                        TransformComponent* transform = entity->getComponent<TransformComponent>();
                        
                        if (renderer && transform) {
                            renderingSystem.submitForRendering(renderer, transform);
                        }
                    }
                }
                
                // Perform actual rendering
                renderingSystem.render();
                
                // Signal that rendering is complete
                renderingCompleted.store(true);
            }
            
            // Limit render thread rate if rendering is too fast
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
    
    void physicsThreadFunc() {
        // Fixed timestep for physics
        const float fixedDt = 1.0f / 60.0f;
        float accumulator = 0.0f;
        
        while (running) {
            {
                std::lock_guard<std::mutex> lock(gameStateMutex);
                
                // Accumulate time
                accumulator += deltaTime;
                
                // Run physics in fixed timesteps
                while (accumulator >= fixedDt) {
                    physicsSystem.update(fixedDt);
                    accumulator -= fixedDt;
                }
            }
            
            // Signal that physics is complete
            physicsCompleted.store(true);
            
            // Wait a bit to avoid spinning
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
    
    void audioThreadFunc() {
        while (running) {
            // Process audio system updates
            audioSystem.update();
            
            // Audio processing is generally less frequent than rendering
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    
    void limitFrameRate(int fps) {
        static auto lastFrameTime = std::chrono::high_resolution_clock::now();
        
        // Calculate target frame duration
        const std::chrono::duration<double> targetFrameDuration(1.0 / fps);
        
        // Get current time
        auto now = std::chrono::high_resolution_clock::now();
        
        // Calculate elapsed time
        std::chrono::duration<double> elapsed = now - lastFrameTime;
        
        // Sleep if we're running too fast
        if (elapsed < targetFrameDuration) {
            std::this_thread::sleep_for(targetFrameDuration - elapsed);
        }
        
        // Update last frame time
        lastFrameTime = std::chrono::high_resolution_clock::now();
    }
};
```

### 11.2.6 Popular Game Engines Using C++

#### Unreal Engine

Epic Games' Unreal Engine is one of the most popular commercial game engines, written primarily in C++. It features:

1. **Blueprint Visual Scripting**: A visual scripting system that compiles down to C++
2. **Comprehensive Editor**: A full-featured editor with real-time preview
3. **Advanced Rendering**: PBR rendering, dynamic lighting, global illumination
4. **Physics**: Integrated PhysX physics engine
5. **Networking**: Robust multiplayer framework
6. **Cross-platform**: Supports multiple platforms including PC, consoles, mobile, VR

Example Unreal Engine C++ class:

```cpp
// Character class in Unreal Engine
#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Constructor
AMyCharacter::AMyCharacter()
{
    // Set this character to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;

    // Create a camera component
    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
    FirstPersonCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
    FirstPersonCameraComponent->bUsePawnControlRotation = true;

    // Set character movement properties
    GetCharacterMovement()->JumpZVelocity = 600.0f;
    GetCharacterMovement()->AirControl = 0.2f;
}

// Called when game starts or when spawned
void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    // Initialize health
    CurrentHealth = MaxHealth;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Update health regeneration
    if (bRegenerateHealth && CurrentHealth < MaxHealth)
    {
        RegenerationTimer += DeltaTime;
        if (RegenerationTimer >= RegenerationInterval)
        {
            RegenerationTimer = 0.0f;
            CurrentHealth = FMath::Min(CurrentHealth + RegenerationAmount, MaxHealth);
        }
    }
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Set up movement bindings
    PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);

    // Set up look bindings
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

    // Set up action bindings
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, this, &AMyCharacter::StopFire);
}

// Handle moving forward/backward
void AMyCharacter::MoveForward(float Value)
{
    if (Value != 0.0f)
    {
        // Find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // Get forward vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

// Handle moving right/left
void AMyCharacter::MoveRight(float Value)
{
    if (Value != 0.0f)
    {
        // Find out which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        
        // Get right vector 
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

// Start weapon firing
void AMyCharacter::StartFire()
{
    if (WeaponComponent)
    {
        WeaponComponent->StartFire();
    }
}

// Stop weapon firing
void AMyCharacter::StopFire()
{
    if (WeaponComponent)
    {
        WeaponComponent->StopFire();
    }
}

// Apply damage to this character
float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    // Apply base damage calculation
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    if (ActualDamage > 0.0f)
    {
        // Decrease health
        CurrentHealth = FMath::Max(CurrentHealth - ActualDamage, 0.0f);

        // Reset regeneration timer when damaged
        RegenerationTimer = 0.0f;

        // Check if dead
        if (CurrentHealth <= 0.0f)
        {
            Die(DamageCauser);
        }
        else
        {
            // Play hit reaction
            PlayHitReaction();
        }
    }

    return ActualDamage;
}

// Handle character death
void AMyCharacter::Die(AActor* Killer)
{
    // Disable input
    DisableInput(nullptr);

    // Set appropriate collision
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
    GetMesh()->SetSimulatePhysics(true);

    // Broadcast death event
    OnCharacterDied.Broadcast(this, Killer);

    // Set timer to respawn or destroy
    GetWorldTimerManager().SetTimer(
        RespawnTimerHandle,
        this,
        &AMyCharacter::HandleRespawn,
        RespawnDelay,
        false
    );
}
```

#### Unity Engine

While Unity primarily uses C# for scripting, its core engine is written in C++. Unity developers can also create native plugins in C++ for performance-critical features.

Example of a C++ native plugin for Unity:

```cpp
#include "UnityNativePlugin.h"
#include "Unity/IUnityGraphics.h"
#include "Unity/IUnityInterface.h"

// Plugin instance data
static IUnityInterfaces* s_UnityInterfaces = nullptr;
static IUnityGraphics* s_UnityGraphics = nullptr;

// Function to handle rendering events from Unity
static void UNITY_INTERFACE_API OnRenderEvent(int eventID)
{
    // Plugin-specific rendering code
    // This would typically interact with the graphics API (OpenGL, DirectX, etc.)
    switch (eventID)
    {
        case 0: // Custom post-processing effect
            ApplyCustomPostProcess();
            break;
            
        case 1: // Custom shader effect
            ApplyCustomShaderEffect();
            break;
    }
}

// Apply a custom post-processing effect
void ApplyCustomPostProcess()
{
    // Implementation depends on the graphics API in use
}

// Apply a custom shader effect
void ApplyCustomShaderEffect()
{
    // Implementation depends on the graphics API in use
}

// Unity plugin load event
extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
UnityPluginLoad(IUnityInterfaces* unityInterfaces)
{
    s_UnityInterfaces = unityInterfaces;
    s_UnityGraphics = unityInterfaces->Get<IUnityGraphics>();
    
    // Register for graphics device events
    s_UnityGraphics->RegisterDeviceEventCallback(OnGraphicsDeviceEvent);
    
    // Run OnGraphicsDeviceEvent(initialize) manually once
    OnGraphicsDeviceEvent(kUnityGfxDeviceEventInitialize);
}

// Unity plugin unload event
extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
UnityPluginUnload()
{
    if (s_UnityGraphics)
    {
        s_UnityGraphics->UnregisterDeviceEventCallback(OnGraphicsDeviceEvent);
    }
    
    s_UnityInterfaces = nullptr;
    s_UnityGraphics = nullptr;
}

// Function exposed to Unity
extern "C" UnityRenderingEvent UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
GetRenderEventFunc()
{
    return OnRenderEvent;
}

// Custom raycast implementation exposed to Unity
extern "C" bool UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
CustomRaycast(float originX, float originY, float originZ,
             float dirX, float dirY, float dirZ,
             float* hitX, float* hitY, float* hitZ)
{
    // Implement custom raycast algorithm
    // This could be an optimized version or use specialized acceleration structures
    
    // For this example, let's do a simple sphere intersection
    const float sphereX = 0.0f, sphereY = 0.0f, sphereZ = 0.0f;
    const float sphereRadius = 1.0f;
    
    float ox = originX - sphereX;
    float oy = originY - sphereY;
    float oz = originZ - sphereZ;
    
    float a = dirX * dirX + dirY * dirY + dirZ * dirZ;
    float b = 2.0f * (ox * dirX + oy * dirY + oz * dirZ);
    float c = ox * ox + oy * oy + oz * oz - sphereRadius * sphereRadius;
    
    float discriminant = b * b - 4.0f * a * c;
    if (discriminant < 0.0f)
    {
        return false; // No intersection
    }
    
    // Calculate intersection point
    float t = (-b - sqrt(discriminant)) / (2.0f * a);
    if (t < 0.0f) 
    {
        t = (-b + sqrt(discriminant)) / (2.0f * a);
        if (t < 0.0f)
        {
            return false; // Intersection behind ray origin
        }
    }
    
    // Calculate hit point
    *hitX = originX + dirX * t;
    *hitY = originY + dirY * t;
    *hitZ = originZ + dirZ * t;
    
    return true;
}
```

### 11.2.7 Future Trends in Game Engine Development

As game engines evolve, several trends are emerging:

1. **Data-Oriented Design**: Moving away from traditional OOP toward more cache-friendly DOD approaches.

2. **Ray Tracing**: Hardware-accelerated ray tracing for realistic lighting and reflections.

3. **Machine Learning Integration**: Using ML for better animations, NPC behavior, and content generation.

4. **Cross-Platform Development**: Engines are focusing on supporting multiple platforms from a single codebase.

5. **Cloud-Based Technologies**: Distributed rendering and computation for more complex simulations.

6. **Procedural Generation**: Advanced algorithms for creating environments, characters, and gameplay elements.

7. **Extended Reality Support**: Better integration of AR/VR/XR technologies.

C++ continues to play a crucial role in these advancements due to its performance characteristics and direct hardware access capabilities.

### 11.2.8 Challenges in Game Engine Development

Game engine developers face several challenges:

1. **Performance vs. Abstraction**: Balancing high-level abstractions with performance requirements.

2. **Cross-Platform Support**: Supporting multiple hardware architectures and operating systems.

3. **Graphics API Evolution**: Keeping up with rapidly changing graphics APIs like DirectX, Vulkan, Metal.

4. **Memory Management**: Preventing fragmentation and ensuring predictable performance.

5. **Multithreading**: Efficiently utilizing multiple cores without introducing race conditions or deadlocks.

6. **Build Times**: Managing large codebases with long compilation times.

7. **Backward Compatibility**: Supporting older content while adding new features.

8. **Asset Pipeline**: Efficiently processing and optimizing assets for different platforms.

C++ addresses many of these challenges through its performance characteristics and flexibility, though it introduces complexity that must be managed through good architecture and coding practices.

### 11.2.9 Resources for Game Engine Developers

For those interested in learning more about game engine development:

1. **Books**:
   - "Game Engine Architecture" by Jason Gregory
   - "Game Programming Patterns" by Robert Nystrom
   - "Physics for Game Developers" by David M. Bourg

2. **Open Source Engines**:
   - Godot Engine: A fully open-source game engine in C++
   - OGRE: Open source graphics rendering engine
   - Box2D: 2D physics engine

3. **Conferences**:
   - Game Developers Conference (GDC)
   - SIGGRAPH
   - CppCon often has game development talks

4. **Online Resources**:
   - Unreal Engine documentation and source code
   - Gamasutra articles on game engine development
   - Graphics programming sites like LearnOpenGL
