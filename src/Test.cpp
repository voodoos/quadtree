#include "pch.h"
#include <forward_list>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <sstream>
#include <vector>

#include "QuadTree.h"

using namespace std;

class TestItem : public QuadValModel {
private:
	int i;

public:
	TestItem(int i, AABB b)
		: QuadValModel{ b }, i{ i }{}
	TestItem(int i, int x, int y, int w, int h)
		: TestItem{ i, AABB {x,y,w,h} } {}

	std::string toString() const {
		return to_string(i) + get_box().toString();
	};
};

int randint(int min, int max) {
	static std::random_device r;
	std::default_random_engine e1(r());
	// Random size:
	std::uniform_int_distribution size_dist(min, max);
	return size_dist(e1);
}

template<typename T, int ME, int MD>
void renderQuadTree(
	SDL_Renderer* r,
	const typename QuadTree<T, ME, MD>::QuadNode& n
) {
	AABB box = n.get_box();
	SDL_Rect rect{ box.get_x(), box.get_y(), box.get_w(), box.get_h() };
	int ro = randint(0, 255);
	int g = randint(0, 255);
	int b = randint(0, 255);
	SDL_SetRenderDrawColor(r, ro, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(
		r, &rect
	);

	for (auto& val : n.get_values()) {
		AABB box = val->get_box();
		SDL_Rect rect{ box.get_x(), box.get_y(), box.get_w(), box.get_h() };
		SDL_SetRenderDrawColor(r, ro, g, b, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(
			r, &rect
		);

	}

	for (auto& child : n.get_children())
		renderQuadTree<T, ME, MD>(r, child);

}

std::unique_ptr<TestItem> randItem(std::random_device& r, int mx, int my) {
	static int i = 0;
	std::default_random_engine e1(r());
	// Random size:
	std::uniform_int_distribution size_dist(1, min(mx, min(my, 10)));
	int size = size_dist(e1);

	std::uniform_int_distribution xy_dist(0, min(mx - size, my - size));
	int x = xy_dist(e1);
	int y = xy_dist(e1);

	return std::make_unique<TestItem>(++i, x, y, size, size);
}

int main(int argc, char *argv[]) {
	std::random_device r;

	std::cout << "Hello World!\n";

	/*std::cout << "Size of QuadNode<int>: " << sizeof(QuadTree<int, 4, 5>::QuadNode > ) << endl;
	std::cout << "Size of QuadNode<short>: " << sizeof(QuadTree<int, 4, 5>::QuadNode) << endl;
	std::cout << "Size of forward_list<int>: " << sizeof(forward_list<int>) << endl;
	std::cout << "Size of short: " << sizeof(short) << endl;
	std::cout << "Size of AABB: " << sizeof(AABB) << endl;*/


	int w = 1000, h = 1000;

	QuadTree<TestItem, 3, 10> qt{ w, h };
	/*cout << qt.toString() << endl;
	qt.insert(randItem(r, w, h));
	qt.insert(randItem(r, w, h));
	qt.insert(randItem(r, w, h));
	qt.insert(randItem(r, w, h));
	qt.insert(randItem(r, w, h));
	qt.insert(randItem(r, w, h));
	cout << qt.toString() << endl;*/

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window =
		SDL_CreateWindow("Hello World!", 100, 100, w, h, SDL_WINDOW_SHOWN);

	SDL_Renderer *renderer =
		SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	qt.insert(std::make_unique<TestItem>(0, 10, 10, 10, 10));
	qt.insert(std::make_unique<TestItem>(0, 550, 550, 10, 10));
	qt.insert(std::make_unique<TestItem>(0, 550, 10, 10, 10));
	qt.insert(std::make_unique<TestItem>(0, 550, 40, 10, 10));
	qt.insert(std::make_unique<TestItem>(0, 550, 25, 10, 10));
	renderQuadTree<TestItem, 3, 10>(renderer, qt.get_root());

	cout << qt << endl;
	SDL_RenderPresent(renderer);

	while (true)
	{
		SDL_Delay(10);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		qt.insert(randItem(r, w, h));
		renderQuadTree<TestItem, 3, 10>(renderer, qt.get_root());
		SDL_RenderPresent(renderer);
	}




	SDL_DestroyWindow(window);
	SDL_Quit();


	return 0;
}
