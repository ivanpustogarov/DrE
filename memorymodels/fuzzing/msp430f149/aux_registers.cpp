extern "C" ref<Expr> usb_setup_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "@" << addr <<"\n";

	//ref<ConstantExpr> addrExpr = ConstantExpr::create(addr, w);
	ref<ConstantExpr> addrExpr = Expr::createPointer(addr);
	ObjectPair op;
	s->addressSpace.resolveOne(addrExpr, op, NULL);
	const MemoryObject * mo = op.first;
	const ObjectState * os = op.second;
	

	std::cerr << "addr in " << addr << "\n"
						<< " guest_address " << mo->guest_address << "\n";


	std::cerr << "mo " << mo << "\n";
	uint64_t offset = addr - mo->guest_address;

	std::cerr	<< "usb_setup_r offset is " << offset << "\n";

	#if 0
	++use_count;
	std::string res_name = "usb_setup_" + llvm::utostr(offset) + "_" 
		+ llvm::utostr(use_count);

	if (offset == 0x0000){ //bmRequestType
		const Array * array = new Array(res_name, w);
		//ref<Expr> res = Expr::createTempRead(array, w, true);
		ref<Expr> res = ConstantExpr::create(0x00, w);
		return res;
	} else if (offset == 0x0001){ //bRequest
		const Array * array = new Array(res_name, w);
		//ref<Expr> res = Expr::createTempRead(array, w, true);
		ref<Expr> res = ConstantExpr::create(0x09, w);
		return res;
	} else if (offset == 0x0002){ //wValue
		//const Array * array = new Array(res_name, w);
		//ref<Expr> res = Expr::createTempRead(array, w, true);
		ref<Expr> res = ConstantExpr::create(0xff, w);
		return res;
	} else if (offset == 0x0004){ //wIndex
		ref<Expr> res = ConstantExpr::create(0x01, w);
		return res;
	} else if (offset == 0x0006){ //wLength
		const Array * array = new Array(res_name, w);
		ref<Expr> res = Expr::createTempRead(array, w, true);
		return res;
	}
	#endif

	if (offset == 0x0000){ //bmRequestType
		ref<Expr> res = ConstantExpr::create(0x00, w);
		return res;
	} else if (offset == 0x0001){ //bRequest
		ref<Expr> res = ConstantExpr::create(0x09, w);
		return res;
	} else if (offset == 0x0002){ //wValue
		ref<Expr> res = ConstantExpr::create(0x01, w);
		return res;
	} else if (offset == 0x0003){ //wValue + 1
		ref<Expr> res = ConstantExpr::create(0x00, w);
		return res;
	} else if (offset == 0x0004){ //wIndex
		ref<Expr> res = ConstantExpr::create(0x00, w);
		return res;
	} else if (offset == 0x0005){ //wIndex + 1
		ref<Expr> res = ConstantExpr::create(0x00, w);
		return res;
	} else if (offset == 0x0006){ //wLength
		ref<Expr> res = ConstantExpr::create(0x00, w);
		return res;
	} else if (offset == 0x0007){ //Length + 1
		ref<Expr> res = ConstantExpr::create(0x00, w);
		return res;
	}

	assert(0 && "unexpected offset in usb_setup_r");


	#if 0
	const Array * array = new Array(res_name, w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
	#endif
}
