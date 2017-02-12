#pragma once
struct GLFWwindow;
class Camera;


typedef void(__cdecl *MouseCB)(Camera&, int bc, int act);
typedef void(__cdecl *KeyCB)(Camera&, int kc, int act);
typedef void(__cdecl *CPCB)(Camera&, double, double);

void KeyCallBck(GLFWwindow *win, int kc, int sc, int act, int mod);
void MouseCallBck(GLFWwindow *win, int bc, int act, int mod);
void CursorCallBck(GLFWwindow *win, double x, double y);
void initInput(GLFWwindow *win, Camera* cam);
void RegisterKCB(KeyCB cb);
void RegisterMCB(MouseCB cb);
void RegisterCCB(CPCB cb);
