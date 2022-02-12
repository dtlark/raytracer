#include <iostream>

#include "Canvas.h" //#include "Tuples.h"
#include "Matrix.h"

using namespace std;

int main() {
	
	Canvas picture = Canvas(250, 250);

	picture.Save("picture");

}
