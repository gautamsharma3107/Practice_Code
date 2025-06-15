# Chapter 11: C++ in the Real World (Part 3)

## 11.2 C++ in Game Engines

Game engines are complex software frameworks that provide developers with tools and systems to create video games without having to build everything from scratch. They typically handle rendering, physics, collision detection, audio, input systems, animation, and more. C++ has been the dominant language in game engine development for decades due to its unique combination of performance and flexibility.

### 11.2.1 Why C++ Dominates Game Development

Several key characteristics make C++ the preferred language for game engine development:

#### 1. Performance

Games are performance-critical applications that must process vast amounts of data in real-time while maintaining high frame rates (typically 30-60+ frames per second):

- **Low-level control**: C++ provides direct memory management without garbage collection pauses
- **Compiled language efficiency**: C++ compiles to highly optimized native code
- **Minimal overhead**: No interpreter or virtual machine adding performance costs
- **SIMD/Vectorization**: C++ allows for explicit use of CPU vector instructions (SSE, AVX)
- **Cache-friendly code**: C++ developers can control memory layout for optimal cache utilization

#### 2. Hardware Access

Game engines need to interact directly with graphics hardware and other system components:

- **Graphics APIs**: Direct access to DirectX, Vulkan, OpenGL, Metal
- **Memory-mapped I/O**: Ability to interact with hardware registers
- **Hardware features**: Access to specialized hardware features like GPU compute
- **Low-level optimization**: Fine control over how code maps to hardware instructions

#### 3. Memory Management Control

Games often have strict memory constraints, especially on consoles and mobile devices:

- **Custom allocators**: Game engines typically implement specialized memory allocators
- **Memory pooling**: Pre-allocation of memory pools to avoid fragmentation
- **Deterministic cleanup**: RAII pattern ensures resources are properly managed
- **Memory layout control**: Explicit control over object layout and alignment

### 11.2.2 Core Components of Game Engines

Let's explore the major components of a game engine and how they're implemented in C++:

#### 1. Rendering Engine

The rendering system is responsible for displaying graphics on screen:

```cpp
class RenderingEngine {
private:
    std::vector<RenderableObject*> renderQueue;
    Camera* activeCamera;
    LightManager* lightManager;
    ShaderManager* shaderManager;
    
    // OpenGL/DirectX/Vulkan context and resources
    GraphicsContext* graphicsContext;
    
public:
    void initialize(GraphicsAPI api = GraphicsAPI::OpenGL) {
        // Initialize graphics context based on API
        graphicsContext = createGraphicsContext(api);
        
        // Initialize managers
        shaderManager = new ShaderManager(graphicsContext);
        lightManager = new LightManager();
        
        // Load standard shaders
        shaderManager->loadShader("standard", "shaders/standard.vert", "shaders/standard.frag");
        shaderManager->loadShader("shadow", "shaders/shadow.vert", "shaders/shadow.frag");
    }
    
    void setActiveCamera(Camera* camera) {
        activeCamera = camera;
    }
    
    void submitForRendering(RenderableObject* object) {
        // Add object to render queue for this frame
        renderQueue.push_back(object);
    }
    
    void render() {
        // Sort objects by material/shader for efficient state changes
        std::sort(renderQueue.begin(), renderQueue.end(), 
                 [](const RenderableObject* a, const RenderableObject* b) {
                     return a->getMaterial()->getShaderID() < b->getMaterial()->getShaderID();
                 });
        
        // Set up view and projection matrices
        Matrix4x4 viewMatrix = activeCamera->getViewMatrix();
        Matrix4x4 projectionMatrix = activeCamera->getProjectionMatrix();
        
        // Render shadow maps first (if enabled)
        renderShadowMaps();
        
        // Clear framebuffer
        graphicsContext->clear(Color(0.1f, 0.1f, 0.2f, 1.0f));
        
        // State tracking for batching optimization
        Material* currentMaterial = nullptr;
        Shader* currentShader = nullptr;
        
        // Render all objects
        for (RenderableObject* object : renderQueue) {
            // Skip objects outside view frustum
            if (!activeCamera->isVisible(object->getBoundingBox())) {
                continue;
            }
            
            // Apply material and shader if different from current
            Material* material = object->getMaterial();
            if (material != currentMaterial) {
                if (material->getShader() != currentShader) {
                    currentShader = material->getShader();
                    currentShader->bind();
                    
                    // Set global uniforms that are the same for all objects with this shader
                    currentShader->setUniform("viewMatrix", viewMatrix);
                    currentShader->setUniform("projectionMatrix", projectionMatrix);
                    
                    // Set lighting uniforms
                    lightManager->setLightUniforms(currentShader);
                }
                
                // Set material properties
                material->apply();
                currentMaterial = material;
            }
            
            // Set per-object uniforms
            currentShader->setUniform("modelMatrix", object->getTransformMatrix());
            
            // Draw the object's mesh
            object->getMesh()->draw(graphicsContext);
        }
        
        // Clear render queue for next frame
        renderQueue.clear();
        
        // Swap buffers
        graphicsContext->swapBuffers();
    }
    
private:
    void renderShadowMaps() {
        // Render the scene from light's perspective for shadow mapping
        // (Implementation details omitted for brevity)
    }
};
```

#### 2. Physics Engine

The physics system simulates physical interactions between game objects:

```cpp
class PhysicsEngine {
private:
    std::vector<RigidBody*> bodies;
    std::vector<Collider*> colliders;
    Vector3 gravity;
    
    // Spatial partitioning for broad-phase collision detection
    OctTree spatialPartitioning;
    
    // Fixed timestep for stable physics
    float fixedTimeStep;
    float accumulator;
    
public:
    PhysicsEngine() : gravity(0, -9.81f, 0), fixedTimeStep(1.0f/60.0f), accumulator(0) {}
    
    void setGravity(const Vector3& g) {
        gravity = g;
    }
    
    void addRigidBody(RigidBody* body) {
        bodies.push_back(body);
        
        // Add body's collider to spatial partitioning
        if (body->getCollider()) {
            colliders.push_back(body->getCollider());
            spatialPartitioning.insert(body->getCollider());
        }
    }
    
    void removeRigidBody(RigidBody* body) {
        // Remove from bodies list
        auto it = std::find(bodies.begin(), bodies.end(), body);
        if (it != bodies.end()) {
            bodies.erase(it);
        }
        
        // Remove collider from spatial partitioning
        if (body->getCollider()) {
            spatialPartitioning.remove(body->getCollider());
            
            auto colliderIt = std::find(colliders.begin(), colliders.end(), body->getCollider());
            if (colliderIt != colliders.end()) {
                colliders.erase(colliderIt);
            }
        }
    }
    
    void update(float deltaTime) {
        // Accumulate time for fixed timestep physics
        accumulator += deltaTime;
        
        // Run physics in fixed timesteps for stability
        while (accumulator >= fixedTimeStep) {
            updatePhysics(fixedTimeStep);
            accumulator -= fixedTimeStep;
        }
    }
    
private:
    void updatePhysics(float dt) {
        // Apply forces (like gravity)
        for (RigidBody* body : bodies) {
            if (!body->isStatic()) {
                body->applyForce(gravity * body->getMass());
            }
        }
        
        // Update velocities based on forces
        for (RigidBody* body : bodies) {
            if (!body->isStatic()) {
                // v = v₀ + a*t
                Vector3 acceleration = body->getAccumulatedForce() * body->getInverseMass();
                body->setVelocity(body->getVelocity() + acceleration * dt);
                
                // Apply damping (simulates air resistance)
                body->setVelocity(body->getVelocity() * (1.0f - body->getDamping() * dt));
                
                // Reset accumulated force
                body->clearAccumulatedForce();
            }
        }
        
        // Detect and resolve collisions
        std::vector<CollisionData> collisions = detectCollisions();
        resolveCollisions(collisions, dt);
        
        // Update positions
        for (RigidBody* body : bodies) {
            if (!body->isStatic()) {
                // p = p₀ + v*t
                Vector3 newPosition = body->getPosition() + body->getVelocity() * dt;
                body->setPosition(newPosition);
            }
        }
        
        // Update spatial partitioning
        updateSpatialPartitioning();
    }
    
    std::vector<CollisionData> detectCollisions() {
        std::vector<CollisionData> collisions;
        
        // Broad-phase: Find potentially colliding pairs using spatial partitioning
        for (Collider* colliderA : colliders) {
            // Query for potential collision candidates
            std::vector<Collider*> potentialColliders = 
                spatialPartitioning.queryPotentialCollisions(colliderA);
            
            // Narrow-phase: Detailed collision test for each pair
            for (Collider* colliderB : potentialColliders) {
                // Skip self-collision
                if (colliderA == colliderB) continue;
                
                // Skip if both objects are static
                if (colliderA->getRigidBody()->isStatic() && 
                    colliderB->getRigidBody()->isStatic()) {
                    continue;
                }
                
                // Perform detailed collision check
                CollisionData collision;
                if (checkCollision(colliderA, colliderB, collision)) {
                    collisions.push_back(collision);
                }
            }
        }
        
        return collisions;
    }
    
    void resolveCollisions(const std::vector<CollisionData>& collisions, float dt) {
        for (const CollisionData& collision : collisions) {
            RigidBody* bodyA = collision.colliderA->getRigidBody();
            RigidBody* bodyB = collision.colliderB->getRigidBody();
            
            // Skip if one of the bodies has been removed
            if (!bodyA || !bodyB) continue;
            
            // Calculate relative velocity
            Vector3 relativeVelocity = bodyB->getVelocity() - bodyA->getVelocity();
            
            // Calculate velocity along normal
            float velAlongNormal = relativeVelocity.dot(collision.normal);
            
            // Skip if objects are moving apart
            if (velAlongNormal > 0) continue;
            
            // Calculate bounciness (coefficient of restitution)
            float restitution = std::min(bodyA->getRestitution(), bodyB->getRestitution());
            
            // Calculate impulse magnitude
            float inverseMassA = bodyA->isStatic() ? 0.0f : bodyA->getInverseMass();
            float inverseMassB = bodyB->isStatic() ? 0.0f : bodyB->getInverseMass();
            float inverseMassSum = inverseMassA + inverseMassB;
            
            if (inverseMassSum == 0.0f) continue; // Both bodies are static
            
            float j = -(1.0f + restitution) * velAlongNormal;
            j /= inverseMassSum;
            
            // Apply impulse
            Vector3 impulse = collision.normal * j;
            
            if (!bodyA->isStatic()) {
                bodyA->setVelocity(bodyA->getVelocity() - impulse * bodyA->getInverseMass());
            }
            
            if (!bodyB->isStatic()) {
                bodyB->setVelocity(bodyB->getVelocity() + impulse * bodyB->getInverseMass());
            }
            
            // Position correction to prevent sinking (using the "bias" method)
            const float percent = 0.2f; // Penetration percentage to correct
            const float slop = 0.01f;   // Allow small penetration for stability
            
            Vector3 correction = collision.normal * 
                                (std::max(collision.penetrationDepth - slop, 0.0f) / 
                                inverseMassSum * percent);
            
            if (!bodyA->isStatic()) {
                bodyA->setPosition(bodyA->getPosition() - correction * bodyA->getInverseMass());
            }
            
            if (!bodyB->isStatic()) {
                bodyB->setPosition(bodyB->getPosition() + correction * bodyB->getInverseMass());
            }
        }
    }
    
    void updateSpatialPartitioning() {
        spatialPartitioning.clear();
        for (Collider* collider : colliders) {
            spatialPartitioning.insert(collider);
        }
    }
};
```

#### 3. Entity-Component System (ECS)

Modern game engines often use a component-based architecture for organizing game objects:

```cpp
// Base Component class
class Component {
public:
    virtual ~Component() = default;
    
    virtual void initialize() {}
    virtual void update(float deltaTime) {}
    
    Entity* getEntity() const { return entity; }
    
    friend class Entity;
    
protected:
    Entity* entity = nullptr;
};

// Transform Component
class TransformComponent : public Component {
private:
    Vector3 position;
    Quaternion rotation;
    Vector3 scale;
    
    // Caching
    Matrix4x4 worldMatrix;
    bool worldMatrixDirty = true;
    
    // Hierarchy
    TransformComponent* parent = nullptr;
    std::vector<TransformComponent*> children;
    
public:
    TransformComponent() : position(0,0,0), rotation(), scale(1,1,1) {}
    
    void setPosition(const Vector3& pos) {
        position = pos;
        setDirty();
    }
    
    void setRotation(const Quaternion& rot) {
        rotation = rot;
        setDirty();
    }
    
    void setScale(const Vector3& s) {
        scale = s;
        setDirty();
    }
    
    Vector3 getPosition() const { return position; }
    Quaternion getRotation() const { return rotation; }
    Vector3 getScale() const { return scale; }
    
    // Parent-child relationship methods
    void setParent(TransformComponent* newParent) {
        if (parent == newParent) return;
        
        // Remove from old parent
        if (parent) {
            auto it = std::find(parent->children.begin(), parent->children.end(), this);
            if (it != parent->children.end()) {
                parent->children.erase(it);
            }
        }
        
        // Set new parent
        parent = newParent;
        
        // Add to new parent
        if (parent) {
            parent->children.push_back(this);
        }
        
        setDirty();
    }
    
    // World space transformations
    Matrix4x4 getWorldMatrix() {
        if (worldMatrixDirty) {
            updateWorldMatrix();
        }
        return worldMatrix;
    }
    
    Vector3 getWorldPosition() {
        return getWorldMatrix().getTranslation();
    }
    
    Quaternion getWorldRotation() {
        return getWorldMatrix().getRotation();
    }
    
private:
    void updateWorldMatrix() {
        // Create local transform matrix
        worldMatrix = Matrix4x4::createTransformMatrix(position, rotation, scale);
        
        // Multiply by parent's world matrix if we have a parent
        if (parent) {
            worldMatrix = parent->getWorldMatrix() * worldMatrix;
        }
        
        worldMatrixDirty = false;
    }
    
    void setDirty() {
        worldMatrixDirty = true;
        
        // Also mark all children dirty
        for (TransformComponent* child : children) {
            child->setDirty();
        }
    }
};

// Mesh Renderer Component
class MeshRendererComponent : public Component {
private:
    Mesh* mesh;
    Material* material;
    bool castsShadows;
    
public:
    MeshRendererComponent() : mesh(nullptr), material(nullptr), castsShadows(true) {}
    
    void initialize() override {
        // Register with rendering system when component is added to entity
        RenderingSystem::getInstance().registerRenderer(this);
    }
    
    void setMesh(Mesh* m) { mesh = m; }
    Mesh* getMesh() const { return mesh; }
    
    void setMaterial(Material* mat) { material = mat; }
    Material* getMaterial() const { return material; }
    
    void setCastsShadows(bool cast) { castsShadows = cast; }
    bool getCastsShadows() const { return castsShadows; }
    
    // Used by the rendering system
    void render(RenderContext& context) {
        if (!mesh || !material) return;
        
        // Get transform
        TransformComponent* transform = entity->getComponent<TransformComponent>();
        if (!transform) return;
        
        // Set up model matrix
        Matrix4x4 modelMatrix = transform->getWorldMatrix();
        
        // Apply material
        material->apply(context);
        
        // Set model matrix uniform
        material->getShader()->setUniform("modelMatrix", modelMatrix);
        
        // Draw mesh
        mesh->draw();
    }
};

// Physics Body Component
class RigidBodyComponent : public Component {
private:
    RigidBody* rigidBody;
    
public:
    RigidBodyComponent() : rigidBody(nullptr) {}
    
    ~RigidBodyComponent() {
        if (rigidBody) {
            PhysicsSystem::getInstance().removeRigidBody(rigidBody);
            delete rigidBody;
        }
    }
    
    void initialize() override {
        // Create physics body
        rigidBody = new RigidBody();
        
        // Set initial transform
        TransformComponent* transform = entity->getComponent<TransformComponent>();
        if (transform) {
            rigidBody->setPosition(transform->getPosition());
            rigidBody->setRotation(transform->getRotation());
        }
        
        // Register with physics system
        PhysicsSystem::getInstance().addRigidBody(rigidBody);
    }
    
    void update(float deltaTime) override {
        // Sync transform with physics body
        TransformComponent* transform = entity->getComponent<TransformComponent>();
        if (!transform || !rigidBody) return;
        
        // Update entity transform from physics simulation
        transform->setPosition(rigidBody->getPosition());
        transform->setRotation(rigidBody->getRotation());
    }
    
    RigidBody* getRigidBody() const { return rigidBody; }
    
    void setMass(float mass) {
        if (rigidBody) rigidBody->setMass(mass);
    }
    
    void applyForce(const Vector3& force) {
        if (rigidBody) rigidBody->applyForce(force);
    }
    
    void applyImpulse(const Vector3& impulse) {
        if (rigidBody) rigidBody->applyImpulse(impulse);
    }
    
    void setStatic(bool isStatic) {
        if (rigidBody) rigidBody->setStatic(isStatic);
    }
};

// Entity class
class Entity {
private:
    std::string name;
    std::vector<std::unique_ptr<Component>> components;
    bool active;
    Scene* scene;
    
public:
    Entity(const std::string& name = "Entity") 
        : name(name), active(true), scene(nullptr) {
        // Entities always have a transform component
        addComponent<TransformComponent>();
    }
    
    // Add a component
    template<typename T, typename... Args>
    T* addComponent(Args&&... args) {
        static_assert(std::is_base_of<Component, T>::value, 
                     "T must derive from Component");
        
        // Check if component of this type already exists
        T* existingComponent = getComponent<T>();
        if (existingComponent) {
            return existingComponent;
        }
        
        // Create component
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        T* componentPtr = component.get();
        
        // Set component's entity
        componentPtr->entity = this;
        
        // Store component
        components.push_back(std::move(component));
        
        // Initialize component
        componentPtr->initialize();
        
        return componentPtr;
    }
    
    // Get a component by type
    template<typename T>
    T* getComponent() const {
        static_assert(std::is_base_of<Component, T>::value, 
                     "T must derive from Component");
        
        for (const auto& component : components) {
            if (T* casted = dynamic_cast<T*>(component.get())) {
                return casted;
            }
        }
        
        return nullptr;
    }
    
    // Update all components
    void update(float deltaTime) {
        if (!active) return;
        
        for (auto& component : components) {
            component->update(deltaTime);
        }
    }
    
    // Get entity name
    const std::string& getName() const { return name; }
    
    // Set entity name
    void setName(const std::string& newName) { name = newName; }
    
    // Check if entity is active
    bool isActive() const { return active; }
    
    // Set entity active state
    void setActive(bool isActive) { active = isActive; }
    
    // Get scene
    Scene* getScene() const { return scene; }
    
    // Friend class Scene can set the scene pointer
    friend class Scene;
};
```

#### 4. Input System

The input system handles user interactions like keyboard, mouse, and gamepad input:

```cpp
class InputSystem {
public:
    enum class KeyState {
        Released,  // Not currently pressed
        Pressed,   // Just pressed this frame
        Held       // Held down from previous frame
    };
    
private:
    // Key state tracking
    std::unordered_map<int, bool> currentKeyStates;
    std::unordered_map<int, bool> previousKeyStates;
    
    // Mouse state tracking
    Vector2 mousePosition;
    Vector2 previousMousePosition;
    Vector2 mouseDelta;
    
    // Gamepad state tracking
    struct GamepadState {
        bool connected = false;
        std::array<float, 6> axes = {}; // Left X/Y, Right X/Y, Triggers L/R
        std::array<bool, 15> buttons = {};
    };
    
    std::array<GamepadState, 4> gamepads;
    
    // Singleton instance
    static InputSystem* instance;
    
public:
    // Singleton accessor
    static InputSystem& getInstance() {
        if (!instance) {
            instance = new InputSystem();
        }
        return *instance;
    }
    
    // Call at start of frame to update input state
    void update() {
        // Save previous states
        previousKeyStates = currentKeyStates;
        previousMousePosition = mousePosition;
        
        // Platform-specific input polling would go here
        pollPlatformInput();
        
        // Calculate mouse delta
        mouseDelta = mousePosition - previousMousePosition;
    }
    
    // Keyboard state checks
    KeyState getKeyState(int keyCode) const {
        bool previouslyPressed = wasKeyPressed(keyCode);
        bool currentlyPressed = isKeyPressed(keyCode);
        
        if (currentlyPressed && !previouslyPressed) {
            return KeyState::Pressed;
        } else if (currentlyPressed && previouslyPressed) {
            return KeyState::Held;
        } else {
            return KeyState::Released;
        }
    }
    
    bool isKeyPressed(int keyCode) const {
        auto it = currentKeyStates.find(keyCode);
        return (it != currentKeyStates.end() && it->second);
    }
    
    bool wasKeyPressed(int keyCode) const {
        auto it = previousKeyStates.find(keyCode);
        return (it != previousKeyStates.end() && it->second);
    }
    
    // Mouse state
    Vector2 getMousePosition() const { return mousePosition; }
    Vector2 getMouseDelta() const { return mouseDelta; }
    
    bool isMouseButtonPressed(int button) const {
        return isKeyPressed(MOUSE_BUTTON_OFFSET + button);
    }
    
    // Gamepad state
    bool isGamepadConnected(int gamepadIndex) const {
        if (gamepadIndex < 0 || gamepadIndex >= static_cast<int>(gamepads.size())) {
            return false;
        }
        return gamepads[gamepadIndex].connected;
    }
    
    float getGamepadAxisValue(int gamepadIndex, int axisIndex) const {
        if (gamepadIndex < 0 || gamepadIndex >= static_cast<int>(gamepads.size()) ||
            !gamepads[gamepadIndex].connected || 
            axisIndex < 0 || axisIndex >= static_cast<int>(gamepads[gamepadIndex].axes.size())) {
            return 0.0f;
        }
        return gamepads[gamepadIndex].axes[axisIndex];
    }
    
    bool isGamepadButtonPressed(int gamepadIndex, int buttonIndex) const {
        if (gamepadIndex < 0 || gamepadIndex >= static_cast<int>(gamepads.size()) ||
            !gamepads[gamepadIndex].connected || 
            buttonIndex < 0 || buttonIndex >= static_cast<int>(gamepads[gamepadIndex].buttons.size())) {
            return false;
        }
        return gamepads[gamepadIndex].buttons[buttonIndex];
    }
    
private:
    // Private constructor for singleton
    InputSystem() {}
    
    // Platform-specific input polling
    void pollPlatformInput() {
        // This would be implemented differently based on platform (Windows, macOS, etc.)
        // and potentially using a library like GLFW, SDL, etc.
        
        // For example, with GLFW:
        // GLFWwindow* window = GetMainWindow();
        // currentKeyStates[GLFW_KEY_W] = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
        // double mouseX, mouseY;
        // glfwGetCursorPos(window, &mouseX, &mouseY);
        // mousePosition = Vector2(static_cast<float>(mouseX), static_cast<float>(mouseY));
    }
    
    // Constants
    static constexpr int MOUSE_BUTTON_OFFSET = 1000;
};

// Initialize the singleton instance pointer
InputSystem* InputSystem::instance = nullptr;
```

### 11.2.3 Memory Management in Game Engines

Memory management is critical in games for performance and stability:

```cpp
// Custom memory allocator for game objects
class GameObjectAllocator {
private:
    // Memory block for a pool of objects
    struct MemoryBlock {
        void* memory;
        size_t blockSize;
        size_t used;
        MemoryBlock* next;
    };
    
    MemoryBlock* firstBlock;
    size_t defaultBlockSize;
    
    // Statistics
    size_t totalAllocated;
    size_t totalUsed;
    int allocationCount;
    
public:
    GameObjectAllocator(size_t blockSize = 1024 * 1024)  // 1MB default block size
        : firstBlock(nullptr), defaultBlockSize(blockSize),
          totalAllocated(0), totalUsed(0), allocationCount(0) {}
    
    ~GameObjectAllocator() {
        // Free all allocated memory
        MemoryBlock* current = firstBlock;
        while (current) {
            MemoryBlock* next = current->next;
            free(current->memory);
            free(current);
            current = next;
        }
    }
    
    // Allocate memory from the pool
    void* allocate(size_t size, size_t alignment = 16) {
        // Ensure minimum alignment
        size = alignUp(size, alignment);
        
        // Find a block with enough space
        MemoryBlock* block = findBlockWithSpace(size);
        if (!block) {
            // No suitable block found, create a new one
            size_t blockSize = std::max(size + sizeof(AllocationHeader), defaultBlockSize);
            block = createMemoryBlock(blockSize);
        }
        
        // Calculate aligned address
        uintptr_t rawAddress = reinterpret_cast<uintptr_t>(block->memory) + block->used;
        uintptr_t misalignment = rawAddress & (alignment - 1);
        size_t padding = (misalignment > 0) ? (alignment - misalignment) : 0;
        
        // Calculate final address
        uintptr_t alignedAddress = rawAddress + padding;
        
        // Store allocation header just before the returned memory
        AllocationHeader* header = reinterpret_cast<AllocationHeader*>(alignedAddress - sizeof(AllocationHeader));
        header->size = size;
        header->padding = padding;
        
        // Update block usage
        block->used += size + padding;
        
        // Update statistics
        totalUsed += size + padding;
        allocationCount++;
        
        // Return aligned address
        return reinterpret_cast<void*>(alignedAddress);
    }
    
    // Deallocate memory (not actually freeing memory in a pool allocator)
    void deallocate(void* ptr) {
        if (!ptr) return;
        
        // In a real game engine, you might implement a more sophisticated 
        // deallocation strategy or use different allocation schemes
        // Here we're just tracking statistics
        AllocationHeader* header = reinterpret_cast<AllocationHeader*>(
            reinterpret_cast<uintptr_t>(ptr) - sizeof(AllocationHeader)
        );
        
        totalUsed -= header->size + header->padding;
        allocationCount--;
    }
    
    // Reset the allocator (free all objects at once)
    void reset() {
        MemoryBlock* block = firstBlock;
        while (block) {
            block->used = 0;
            block = block->next;
        }
        
        totalUsed = 0;
        allocationCount = 0;
    }
    
    // Statistics
    size_t getTotalAllocated() const { return totalAllocated; }
    size_t getTotalUsed() const { return totalUsed; }
    int getAllocationCount() const { return allocationCount; }
    
private:
    // Header stored before each allocation
    struct AllocationHeader {
        size_t size;
        size_t padding;
    };
    
    // Helper method to align values
    size_t alignUp(size_t value, size_t alignment) {
        return (value + alignment - 1) & ~(alignment - 1);
    }
    
    // Find a memory block with enough space
    MemoryBlock* findBlockWithSpace(size_t size) {
        MemoryBlock* block = firstBlock;
        while (block) {
            size_t availableSpace = block->blockSize - block->used;
            if (availableSpace >= size + sizeof(AllocationHeader)) {
                return block;
            }
            block = block->next;
        }
        return nullptr;
    }
    
    // Create a new memory block
    MemoryBlock* createMemoryBlock(size_t blockSize) {
        // Allocate block header
        MemoryBlock* block = static_cast<MemoryBlock*>(malloc(sizeof(MemoryBlock)));
        
        // Allocate block memory
        block->memory = malloc(blockSize);
        block->blockSize = blockSize;
        block->used = 0;
        
        // Add to linked list of blocks
        block->next = firstBlock;
        firstBlock = block;
        
        // Update statistics
        totalAllocated += blockSize;
        
        return block;
    }
};

// Usage example:
// GameObjectAllocator allocator;
// Player* player = new(allocator.allocate(sizeof(Player))) Player();
// allocator.deallocate(player);
```

### 11.2.4 Data-Oriented Design

Modern game engines often use data-oriented design for better performance:

```cpp
// Traditional object-oriented approach
class GameObject {
private:
    Vector3 position;
    Quaternion rotation;
    Vector3 scale;
    Mesh* mesh;
    Material* material;
    PhysicsBody* physics;
    
public:
    void update(float deltaTime) {
        // Update logic
        if (physics) {
            position = physics->getPosition();
            rotation = physics->getRotation();
        }
    }
    
    void render() {
        // Render the object
        if (mesh && material) {
            Matrix4x4 transform = calculateTransform();
            material->bind();
            mesh->render(transform);
        }
    }
};

// Data-oriented approach using Structure of Arrays (SoA)
class GameObjectSystem {
private:
    // Components stored in parallel arrays for better cache coherency
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
    size_t capacity = 0;
    size_t count = 0;
    
public:
    GameObjectSystem(size_t initialCapacity = 1000) {
        // Reserve space in all arrays
        transforms.positions.reserve(initialCapacity);
        transforms.rotations.reserve(initialCapacity);
        transforms.scales.reserve(initialCapacity);
        
        renderers.meshes.reserve(initialCapacity);
        renderers.materials.reserve(initialCapacity);
        
        physics.bodies.reserve(initialCapacity);
        physics.hasPhysics.reserve(initialCapacity);
        
        active.reserve(initialCapacity);
        
        capacity = initialCapacity;
    }
    
    // Create a new entity
    size_t createEntity() {
        size_t entityId = count++;
        
        // Ensure capacity
        if (entityId >= capacity) {
            enlargeCapacity();
        }
        
        // Initialize component data
        transforms.positions.push_back(Vector3(0, 0, 0));
        transforms.rotations.push_back(Quaternion::identity());
        transforms.scales.push_back(Vector3(1, 1, 1));
        
        renderers.meshes.push_back(nullptr);
        renderers.materials.push_back(nullptr);
        
        physics.bodies.push_back(nullptr);
        physics.hasPhysics.push_back(false);
        
        active.push_back(true);
        
        return entityId;
    }
    
    // Update physics and transform data
    void updatePhysics(float deltaTime) {
        // Process all physics bodies in one batch for better cache utilization
        for (size_t i = 0; i < count; ++i) {
            if (!active[i] || !physics.hasPhysics[i]) continue;
            
            PhysicsBody* body = physics.bodies[i];
            if (body) {
                // Update transform from physics simulation
                transforms.positions[i] = body->getPosition();
                transforms.rotations[i] = body->getRotation();
            }
        }
    }
    
    // Render all entities efficiently
    void render(RenderContext& context) {
        // First sort by material to minimize state changes
        std::vector<size_t> renderOrder;
        renderOrder.reserve(count);
        
        for (size_t i = 0; i < count; ++i) {
            if (active[i] && renderers.meshes[i] && renderers.materials[i]) {
                renderOrder.push_back(i);
            }
        }
        
        std::sort(renderOrder.begin(), renderOrder.end(), 
                 [this](size_t a, size_t b) {
                     return renderers.materials[a] < renderers.materials[b];
                 });
        
        // Render sorted entities
        Material* currentMaterial = nullptr;
        
        for (size_t entityIdx : renderOrder) {
            // Set material only when it changes
            if (renderers.materials[entityIdx] != currentMaterial) {
                if (currentMaterial) {
                    currentMaterial->unbind();
                }
                
                currentMaterial = renderers.materials[entityIdx];
                currentMaterial->bind();
            }
            
            // Calculate transform matrix
            Matrix4x4 transform = Matrix4x4::createTransformMatrix(
                transforms.positions[entityIdx],
                transforms.rotations[entityIdx],
                transforms.scales[entityIdx]
            );
            
            // Set transform uniform
            context.setModelMatrix(transform);
            
            // Draw mesh
            renderers.meshes[entityIdx]->draw();
        }
        
        // Unbind last material
        if (currentMaterial) {
            currentMaterial->unbind();
        }
    }
    
    // Setters for entity components
    void setTransform(size_t entityId, const Vector3& position, 
                     const Quaternion& rotation, const Vector3& scale) {
        if (entityId >= count) return;
        
        transforms.positions[entityId] = position;
        transforms.rotations[entityId] = rotation;
        transforms.scales[entityId] = scale;
    }
    
    void setRenderer(size_t entityId, Mesh* mesh, Material* material) {
        if (entityId >= count) return;
        
        renderers.meshes[entityId] = mesh;
        renderers.materials[entityId] = material;
    }
    
    void setPhysics(size_t entityId, PhysicsBody* body) {
        if (entityId >= count) return;
        
        physics.bodies[entityId] = body;
        physics.hasPhysics[entityId] = (body != nullptr);
    }
    
private:
    void enlargeCapacity() {
        size_t newCapacity = capacity * 2;
        
        transforms.positions.reserve(newCapacity);
        transforms.rotations.reserve(newCapacity);
        transforms.scales.reserve(newCapacity);
        
        renderers.meshes.reserve(newCapacity);
        renderers.materials.reserve(newCapacity);
        
        physics.bodies.reserve(newCapacity);
        physics.hasPhysics.reserve(newCapacity);
        
        active.reserve(newCapacity);
        
        capacity = newCapacity;
    }
};
```

### 11.2.5 Game Loop and Time Management

The game loop is the backbone of any game engine:

```cpp
class GameEngine {
private:
    bool running = false;
    double targetFrameRate = 60.0;
    double targetFrameTime = 1.0 / 60.0;  // In seconds
    
    // Game state
    Scene* activeScene = nullptr;
    
    // Core systems
    RenderingEngine* renderingEngine;
    PhysicsEngine* physicsEngine;
    AudioEngine* audioEngine;
    InputSystem* inputSystem;
    
    // Timing
    double lastFrameTime;
    double deltaTime;
    
    // Performance metrics
    double fpsUpdateTime = 0.0;
    int frameCount = 0;
    double currentFps = 0.0;
    
public:
    GameEngine() {
        // Create engine systems
        renderingEngine = new RenderingEngine();
        physicsEngine = new PhysicsEngine();
        audioEngine = new AudioEngine();
        inputSystem = &InputSystem::getInstance();
    }
    
    ~GameEngine() {
        delete renderingEngine;
        delete physicsEngine;
        delete audioEngine;
    }
    
    void initialize() {
        // Initialize all engine systems
        renderingEngine->initialize();
        physicsEngine->initialize();
        audioEngine->initialize();
        
        lastFrameTime = getCurrentTime();
        running = true;
    }
    
    void run() {
        initialize();
        
        // Main game loop
        while (running) {
            // Process one frame
            tick();
        }
        
        shutdown();
    }
    
    void setScene(Scene* scene) {
        activeScene = scene;
    }
    
    void setTargetFrameRate(double fps) {
        targetFrameRate = fps;
        targetFrameTime = 1.0 / fps;
    }
    
    double getFPS() const {
        return currentFps;
    }
    
private:
    void tick() {
        // Calculate delta time
        double currentTime = getCurrentTime();
        deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;
        
        // Cap delta time to prevent "spiral of death" on slow frames
        if (deltaTime > 0.25) {
            deltaTime = 0.25;
        }
        
        // Update FPS counter
        frameCount++;
        fpsUpdateTime += deltaTime;
        
        if (fpsUpdateTime >= 1.0) {
            currentFps = frameCount / fpsUpdateTime;
            frameCount = 0;
            fpsUpdateTime = 0.0;
        }
        
        // Process input
        inputSystem->update();
        
        // Check if we should quit
        if (inputSystem->isKeyPressed(KeyCode::Escape)) {
            running = false;
            return;
        }
        
        // Update game logic and physics
        update(deltaTime);
        
        // Render the scene
        render();
        
        // Limit frame rate if needed
        double frameEndTime = getCurrentTime();
        double frameTime = frameEndTime - currentTime;
        double sleepTime = targetFrameTime - frameTime;
        
        if (sleepTime > 0) {
            sleep(sleepTime);
        }
    }
    
    void update(double dt) {
        // Skip if no active scene
        if (!activeScene) return;
        
        // Update physics (may use fixed timestep internally)
        physicsEngine->update(dt);
        
        // Update scene entities
        activeScene->update(dt);
        
        // Update audio
        audioEngine->update(dt);
    }
    
    void render() {
        // Skip if no active scene
        if (!activeScene) return;
        
        // Set camera
        Camera* mainCamera = activeScene->getMainCamera();
        if (mainCamera) {
            renderingEngine->setActiveCamera(mainCamera);
        }
        
        // Clear previous frame
        renderingEngine->clear();
        
        // Render the scene
        activeScene->render(*renderingEngine);
        
        // Finish rendering and display the frame
        renderingEngine->present();
    }
    
    void shutdown() {
        // Cleanup resources
        if (activeScene) {
            delete activeScene;
        }
    }
    
    double getCurrentTime() {
        // Platform-specific time function
        // For example, using std::chrono:
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = now.time_since_epoch();
        auto seconds = std::chrono::duration_cast<std::chrono::duration<double>>(duration);
        return seconds.count();
    }
    
    void sleep(double seconds) {
        // Platform-specific sleep function
        // For example, using std::this_thread::sleep_for:
        std::this_thread::sleep_for(std::chrono::duration<double>(seconds));
    }
};
```

### 11.2.6 Popular Game Engines Using C++

#### 1. Unreal Engine

Epic Games' Unreal Engine is one of the most popular commercial game engines, using C++ as its primary language with a visual scripting system called Blueprints built on top.

**Key Features**:
- Powerful rendering engine with real-time global illumination
- Visual scripting via Blueprints
- Advanced physics and animation systems
- Robust networking capabilities
- Built-in VR/AR support
- Extensive marketplace for assets and plugins

**Example of Unreal Engine C++ class**:

```cpp
// Example PlayerCharacter class in Unreal Engine
#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

APlayerCharacter::APlayerCharacter()
{
    // Create a camera boom
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f;
    CameraBoom->bUsePawnControlRotation = true;
    
    // Create a follow camera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;
    
    // Set character movement properties
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;
    
    // Don't rotate when the controller rotates
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    // Set up gameplay key bindings
    check(PlayerInputComponent);
    
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
    
    PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
    
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void APlayerCharacter::MoveForward(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        // Find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        
        // Get forward vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void APlayerCharacter::MoveRight(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        // Find out which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        
        // Get right vector 
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        
        // Add movement in that direction
        AddMovementInput(Direction, Value);
    }
}
```

#### 2. Unity

While Unity primarily uses C# for game scripting, its core engine is written in C++. Unity also allows developers to write native C++ plugins for performance-critical code.

```cpp
// Example C++ plugin for Unity
#include "Unity/IUnityInterface.h"
#include "PhysicsSimulation.h"

static PhysicsSimulation* g_PhysicsSim = nullptr;

// Unity plugin load
extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API 
UnityPluginLoad(IUnityInterfaces* unityInterfaces)
{
    // Create physics simulation
    g_PhysicsSim = new PhysicsSimulation();
    g_PhysicsSim->Initialize();
}

// Unity plugin unload
extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API 
UnityPluginUnload()
{
    if (g_PhysicsSim)
    {
        g_PhysicsSim->Shutdown();
        delete g_PhysicsSim;
        g_PhysicsSim = nullptr;
    }
}

// Function called from Unity to update physics
extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API 
UpdatePhysicsSimulation(float deltaTime)
{
    if (g_PhysicsSim)
    {
        g_PhysicsSim->Update(deltaTime);
    }
}

// Function to get particle positions
extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API 
GetParticlePositions(int* count, float* positions)
{
    if (g_PhysicsSim)
    {
        g_PhysicsSim->GetParticleData(count, positions);
    }
}
```

#### 3. CryEngine

CryEngine is another C++ based engine, known for its graphical fidelity:

```cpp
// Example CryEngine entity class
#include <CryEntitySystem/IEntityComponent.h>
#include <CryPhysics/IPhysics.h>

class CPlayerComponent : public IEntityComponent
{
public:
    // IEntityComponent
    virtual void Initialize() override
    {
        m_pEntity->LoadGeometry(0, "Objects/Characters/Player/player.cgf");
        
        // Add a physics component
        SEntityPhysicalizeParams physParams;
        physParams.type = PE_LIVING;
        physParams.mass = 90.0f;
        m_pEntity->Physicalize(physParams);
        
        // Listen for input events
        m_pInput = gEnv->pInput;
        m_pInput->AddEventListener(this);
    }
    
    virtual void ProcessEvent(SEntityEvent& event) override
    {
        switch(event.event)
        {
            case ENTITY_EVENT_UPDATE:
            {
                const float deltaTime = event.fParam[0];
                UpdateMovement(deltaTime);
                break;
            }
        }
    }
    
    virtual void OnInputEvent(const SInputEvent& event) override
    {
        // Handle input events
        if (event.keyId == eKI_W && event.state == eIS_Pressed)
        {
            m_isMovingForward = true;
        }
        else if (event.keyId == eKI_W && event.state == eIS_Released)
        {
            m_isMovingForward = false;
        }
        
        // Handle other input...
    }
    
private:
    void UpdateMovement(float deltaTime)
    {
        if (!m_isMovingForward)
            return;
        
        // Get current position & rotation
        Matrix34 transform = m_pEntity->GetWorldTM();
        Vec3 position = transform.GetTranslation();
        
        // Move forward
        Vec3 forward = transform.GetColumn1().normalized();
        position += forward * m_moveSpeed * deltaTime;
        
        // Update entity position
        transform.SetTranslation(position);
        m_pEntity->SetWorldTM(transform);
    }
    
    IInput* m_pInput = nullptr;
    bool m_isMovingForward = false;
    float m_moveSpeed = 5.0f;
};
```

### 11.2.7 Challenges in C++ Game Engine Development

Despite its strengths, C++ presents several challenges in game engine development:

1. **Compilation Times**: Large C++ projects can have lengthy build times
   - Solution: Precompiled headers, unity builds, modules (C++20)

2. **Memory Management**: Manual memory management can lead to leaks and crashes
   - Solution: Smart pointers, custom allocators, RAII pattern

3. **Platform Differences**: Supporting multiple platforms requires handling differences
   - Solution: Platform abstraction layers, conditional compilation

4. **Multithreading Complexity**: C++ multithreading requires careful synchronization
   - Solution: Task-based parallelism, thread pools, lock-free data structures

5. **Legacy Code**: Many game engines contain old code that's hard to modernize
   - Solution: Incremental modernization, clear interfaces, comprehensive testing

### 11.2.8 Modern C++ Features in Game Engines

Modern C++ (C++11 and beyond) introduced many features beneficial for game development:

1. **Move Semantics**: Efficient transfer of resources without expensive copies
   ```cpp
   // Move constructor example
   class Mesh {
   private:
       std::vector<Vertex> vertices;
       std::vector<unsigned int> indices;
       unsigned int vao, vbo, ebo;  // OpenGL handles
       
   public:
       // Move constructor
       Mesh(Mesh&& other) noexcept
           : vertices(std::move(other.vertices)),
             indices(std::move(other.indices)),
             vao(other.vao), vbo(other.vbo), ebo(other.ebo) {
           // Invalidate other's OpenGL handles
           other.vao = other.vbo = other.ebo = 0;
       }
       
       // Move assignment
       Mesh& operator=(Mesh&& other) noexcept {
           if (this != &other) {
               // Clean up current resources
               if (vao != 0) glDeleteVertexArrays(1, &vao);
               if (vbo != 0) glDeleteBuffers(1, &vbo);
               if (ebo != 0) glDeleteBuffers(1, &ebo);
               
               // Move data from other
               vertices = std::move(other.vertices);
               indices = std::move(other.indices);
               vao = other.vao;
               vbo = other.vbo;
               ebo = other.ebo;
               
               // Invalidate other's OpenGL handles
               other.vao = other.vbo = other.ebo = 0;
           }
           return *this;
       }
   };
   ```

2. **Lambda Expressions**: Convenient for callbacks and short algorithms
   ```cpp
   // Using lambdas for event callbacks
   inputSystem.registerKeyCallback(KeyCode::Space, [this](KeyState state) {
       if (state == KeyState::Pressed) {
           player->jump();
       }
   });
   
   // Using lambdas for custom sorting
   std::sort(renderables.begin(), renderables.end(), 
           [](const Renderable& a, const Renderable& b) {
                // Sort by material first, then by mesh
                if (a.material->getID() != b.material->getID())
                    return a.material->getID() < b.material->getID();
                return a.mesh->getID() < b.mesh->getID();
            });
   ```

3. **Smart Pointers**: Safer memory management
   ```cpp
   // Using unique_ptr for exclusive ownership
   std::unique_ptr<Texture> loadTexture(const std::string& filename) {
       auto texture = std::make_unique<Texture>();
       if (!texture->load(filename)) {
           return nullptr;
       }
       return texture;
   }
   
   // Using shared_ptr for shared resources
   class Material {
   private:
       std::shared_ptr<Shader> shader;
       std::shared_ptr<Texture> diffuseMap;
       std::shared_ptr<Texture> normalMap;
       
   public:
       void setShader(std::shared_ptr<Shader> s) { shader = s; }
       void setDiffuseMap(std::shared_ptr<Texture> t) { diffuseMap = t; }
       void setNormalMap(std::shared_ptr<Texture> t) { normalMap = t; }
   };
   ```

4. **constexpr**: Compile-time computation
   ```cpp
   // Compile-time hash function for string literals
   constexpr uint32_t hashString(const char* str, size_t length) {
       uint32_t hash = 5381;
       for (size_t i = 0; i < length; ++i) {
           hash = ((hash << 5) + hash) + static_cast<unsigned char>(str[i]);
       }
       return hash;
   }
   
   // Usage
   constexpr uint32_t textureId = hashString("diffuse_map", 11);
   ```

### 11.2.9 Future Trends in C++ Game Engines

Several trends are shaping the future of C++ game engines:

1. **Data-Oriented Design**: Focusing on data layout and processing for better cache utilization
2. **Parallelism and Concurrency**: Greater emphasis on multi-core utilization
3. **Modular Design**: More modular engines with plug-and-play components
4. **Real-Time Ray Tracing**: Adoption of hardware-accelerated ray tracing technology
5. **Machine Learning Integration**: Using ML for animation, procedural generation, and AI
6. **Cloud and Distributed Computing**: Offloading complex computations to the cloud
7. **WebAssembly Support**: Compiling C++ to run in browsers via WebAssembly

As hardware continues to evolve and new C++ standards emerge, game engines will continue to leverage the language's unique combination of high performance and expressive abstractions to create ever more immersive and complex gaming experiences.
