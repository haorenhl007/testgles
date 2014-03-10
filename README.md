For use ANGLE backend you need:

1. Compile ANGLE from source code for .lib and .dll files (libEGL, libGLESv2)
2. Modify the SDL2 source code and compile for .lib and .dll files (SDL2)

--- a/src/video/windows/SDL_windowsopengl.c
+++ b/src/video/windows/SDL_windowsopengl.c
@@ -398,7 +398,7 @@
     /* Check for WGL_EXT_create_context_es2_profile */
     _this->gl_data->HAS_WGL_EXT_create_context_es2_profile = SDL_FALSE;
     if (HasExtension("WGL_EXT_create_context_es2_profile", extensions)) {
-        _this->gl_data->HAS_WGL_EXT_create_context_es2_profile = SDL_TRUE;
+        _this->gl_data->HAS_WGL_EXT_create_context_es2_profile = SDL_FALSE;
     }

     _this->gl_data->wglMakeCurrent(hdc, NULL);
