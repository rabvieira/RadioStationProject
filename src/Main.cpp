#include <iostream>
#include "RadioStation.h"
#include "User.h"
#include "MusicTrack.h"
#include "Utilities.h"
using namespace std;

int main(){
	Utilities::Init(); // Inicializa Utilities lib
	RadioStation r("PanicStation"); //cria um objeto do tipo RadioStation
	r.interfaceUser();				//invoca o metodo de interacao com o utilizador
	return(0);
}
