#include "IDrawable.h"
#include "window.h"
#include "camera.h"
#include "engine.h"

#include <iostream>
#include <ctime>

constexpr uint w=480;
constexpr uint h=480;


using namespace std;

void f() {
  clock_t begin = clock();


  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
}

int main(int argc, char* argv[])
{
	mesh cube = mesh::load_from_obj("resource/ship.obj");
    Drawable drawObj { cube };
	drawObj.setTranslate(-10, 1, 35.0f);

	Camera cam {vec3d {0, 0, 0}};

	Engine engine;
	engine.set_projection(w/h, 60, 0.5f, 1000.0f);

    Window* win = new Window {"3D engine", w, h};

	float t=1;

    SDL_Keycode key;
	SDL_Event event;
	while (win->running()) {
		while(SDL_PollEvent(&event))
		{
			switch(event.type) 
			{
			case SDL_QUIT:
                win->isRunning = false;
				break;
			}
		}

		drawObj.setRotate(t,  0, -t);
		auto tris = engine.draw(&drawObj, &cam);

		t+=0.1;

		win->update();
		win->render(tris);
		SDL_RenderPresent(win->_renderer);
	}
	delete win;

	return 0;
}
