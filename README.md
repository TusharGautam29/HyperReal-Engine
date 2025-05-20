# HyperReal Game Engine 🎮✨

[![View on GitHub](https://img.shields.io/badge/View%20on-GitHub-000?logo=github&style=flat-square)](https://github.com/TusharGautam29/HyperReal-Engine)

HyperReal is a lightweight yet powerful 2D game engine designed for developers who want to build games **without diving into low-level graphics APIs** like OpenGL or managing raw Win32 boilerplate. Whether you're a beginner or an indie dev, HyperReal gives you a simple way to start making games — fast.

## ⚡ Why HyperReal?

Game development should be about **designing the game**, not fighting your engine. HyperReal gives you:

- **A plug-and-play layer system** — no OpenGL knowledge needed
- **Ready-to-use rendering commands** (quads, textures, rotations)
- **ImGui-based user interface** for live debugging or game editors
- **Minimal API surface** with sane defaults
- **Fully featured 2D renderer**, with 3D support coming soon

## 🔧 Engine Architecture

You build your game by creating **layers**, each represented as a C++ class with the following methods:
## 🧱 Game Layer API

To build a game, you inherit from `HyperR::Layer` and define a custom layer that overrides a few core methods. These are the public hooks you implement:

### 🔩 Lifecycle Methods

- **`OnAttach()`**  
  Called when the layer is added to the engine. Use this to load assets, set up game state, etc.

- **`OnDetach()`**  
  Called when the layer is removed. Clean up resources here.

- **`OnUpdate(Timestep ts)`**  
  Runs every frame. Put all your game logic and rendering here.

- **`OnImGuiRender()`**  
  Used to draw ImGui-based debug panels or tools.

- **`OnEvent(Event& e)`**  
  Central event handler for things like input, window events, etc.

---

### 🧠 Custom Event Hooks

- **`OnMouseButtonPressed(MouseButtonPressedEvent& e)`**  
  Triggered when a mouse button is pressed. Useful for interaction logic.

- **`OnWindowResize(WindowResizeEvent& e)`**  
  Adjusts camera or layout when the game window is resized.

---

### 🎮 Layer-Specific Systems

- **`CreateCamera(uint32_t width, uint32_t height)`**  
  Initializes the orthographic camera for this layer.

---

## 🎮 Game Layer State Variables

- **`m_Camera`**  
  A scoped orthographic camera that handles view/projection for 2D rendering.

- **`m_Level`**  
  A user-defined `Level` object. Contains level data, tiles, entities, etc.

- **`m_Font`**  
  An ImFont pointer for rendering custom fonts in ImGui UI.

- **`m_Time`**  
  Float tracking elapsed time. Useful for animations or logic timing.

- **`m_Blink`**  
  A bool flag, commonly used for blinking UI elements or state toggles.

---

### 🎮 GameState Enum

Defines the current state of the game. Helps manage logic flow.

```cpp
enum class GameState {
    Play = 0,
    MainMenu = 1,
    GameOver = 2
};
```
## 🧪 Example in Action

To see this engine in action, check out a real game built entirely with HyperReal:  
👉 [Flappy Bird Clone](https://github.com/TusharGautam29/Flappy-Bird-Clone)

This project demonstrates the full lifecycle of a game using layers, rendering, input handling, and game state transitions — all powered by HyperReal.

