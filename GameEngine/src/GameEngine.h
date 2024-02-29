#pragma once

// Basic
#include "GameEngine/Core/Application.h"
#include "GameEngine/Core/Log.h"
#include "GameEngine/Core/TimeStep.h"
#include "GameEngine/Core/Timer.h"
#include "GameEngine/Core/Layer.h"
#include "GameEngine/Core/Input.h"
#include "GameEngine/Core/KeyCodes.h"
#include "GameEngine/Core/MouseButtonCodes.h"

// Event
#include "GameEngine/Event/KeyEvent.h"
#include "GameEngine/Event/MouseEvent.h"

// Renderer
#include "GameEngine/Render/Shader.h"
#include "GameEngine/Render/VertexArray.h"
#include "GameEngine/Render/Buffer.h"
#include "GameEngine/Render/Framebuffer.h"
#include "GameEngine/Render/Texture.h"
#include "GameEngine/Render/Render2D.h"
#include "GameEngine/Render/RenderCommand.h"

// EcsFramework
#include "GameEngine/EcsFramework/Component/Basic/IDComponent.h"
#include "GameEngine/EcsFramework/Component/Basic/TagComponent.h"
#include "GameEngine/EcsFramework/Component/Transform/TransformComponent.h"
#include "GameEngine/EcsFramework/Component/Sprite/SpriteComponent.h"
#include "GameEngine/EcsFramework/Component/Camera/CameraComponent.h"
#include "GameEngine/EcsFramework/Component/Light/PointLightComponent.h"
#include "GameEngine/EcsFramework/Component/Mesh/MeshComponent.h"
#include "GameEngine/EcsFramework/System/Render/SystemRender2D.h"
#include "GameEngine/EcsFramework/System/Render/SystemRender3D.h"
#include "GameEngine/EcsFramework/Level/Level.h"
#include "GameEngine/EcsFramework/Entity/Entity.h"

// other
#include "GameEngine/Camera/EditorCamera.h"
#include "GameEngine/Mesh/Mesh.h"
#include "GameEngine/Mesh/SubMesh.h"
#include "GameEngine/Render/RayTrace/RayTrace.h"

// Manager
#include "GameEngine/Manager/ConfigManager.h"