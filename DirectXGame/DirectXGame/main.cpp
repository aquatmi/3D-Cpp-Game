#include "AppWindow.h"
#include <stdexcept>

int main() {
	try {
		AppWindow app;

		if (app.init()) {
			while (app.isRun()) {

				app.broadcast();
			}
		}
	}
	catch (const std::runtime_error& error) {
		MessageBox(nullptr, L"Fix the error message you nugget", L"An error has occured", MB_OK);
	}
	
	return 0;
}