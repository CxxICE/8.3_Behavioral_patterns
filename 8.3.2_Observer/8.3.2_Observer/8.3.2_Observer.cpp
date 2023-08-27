#include <iostream>

#include "Observed.h"
#include "Observer.h"
#include "WarningObserver.h"
#include "ErrorObserver.h"
#include "FatalErrorObserver.h"

int main()
{		
	Observed *obj = new Observed;
	WarningObserver *wo = new WarningObserver;
	ErrorObserver *eo = new ErrorObserver;
	FatalErrorObserver *fo = new FatalErrorObserver;

	obj->AddObserver(wo);
	obj->AddObserver(eo);
	obj->AddObserver(fo);

	std::cout << "\x1B[36m" << "Section 1, 3 observers: warning + error + fatalError\n" << "\x1B[0m";
	obj->warning("Warning 1");
	obj->error("Error 1");
	obj->fatalError("FatalError 1");

	delete wo;
	std::cout << "\x1B[36m" << "\n\nSection 2, 2 observers: error + fatalError (warning deleted)\n" << "\x1B[0m";
	obj->warning("Warning 2");
	obj->error("Error 2");
	obj->fatalError("FatalError 2");

	delete eo;
	delete fo;
	delete obj;
	
	return 0;	
}
