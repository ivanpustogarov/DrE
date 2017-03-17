
extern "C" bool CRC_value_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CRC_value_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"CRC_value_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}extern "C" bool REF_calibration_length_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> REF_calibration_length_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::create(0x06, w);
	return res;
}


extern "C" bool REF_25reference_factor_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> REF_25reference_factor_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"REF_25reference_factor_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}extern "C" bool Peripheral_descriptor_tag_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> Peripheral_descriptor_tag_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::create(0x02, w);
	return res;
}


extern "C" bool ADC12_gain_factor_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12_gain_factor_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12_gain_factor_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool REF_20reference_factor_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> REF_20reference_factor_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"REF_20reference_factor_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12_25temp30_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12_25temp30_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12_25temp30_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12_20temp85_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12_20temp85_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12_20temp85_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}extern "C" bool Device_ID2_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> Device_ID2_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::create(0x21, w);
	return res;
}

extern "C" bool CRC_length_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> CRC_length_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::create(0x06, w);
	return res;
}


extern "C" bool ADC12_15temp85_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12_15temp85_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12_15temp85_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}extern "C" bool Die_record_tag_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> Die_record_tag_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::create(0x08, w);
	return res;
}

extern "C" bool REF_calibration_tag_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> REF_calibration_tag_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::create(0x12, w);
	return res;
}


extern "C" bool Firmware_revision_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> Firmware_revision_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"Firmware_revision_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}extern "C" bool Lot_wafer_id_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> Lot_wafer_id_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::create(0x01020304, w);
	return res;
}


extern "C" bool Test_results_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> Test_results_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"Test_results_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12_20temp30_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12_20temp30_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12_20temp30_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}extern "C" bool Die_x_pos_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> Die_x_pos_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::create(0x0001, w);
	return res;
}

extern "C" bool Device_ID_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> Device_ID_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::create(0x55, w);
	return res;
}

extern "C" bool Info_length_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> Info_length_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::create(0x06, w);
	return res;
}


extern "C" bool ADC12_15temp30_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12_15temp30_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12_15temp30_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}extern "C" bool ADC12_calibration_tag_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12_calibration_tag_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::create(0x11, w);
	return res;
}


extern "C" bool Hardware_revision_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> Hardware_revision_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"Hardware_revision_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool ADC12_25temp85_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12_25temp85_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12_25temp85_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}extern "C" bool ADC12_calibration_length_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12_calibration_length_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::create(0x10, w);
	return res;
}

extern "C" bool Peripheral_descriptor_length_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> Peripheral_descriptor_length_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::create(0x64, w);
	return res;
}

extern "C" bool Die_record_length_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> Die_record_length_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::create(0x0A, w);
	return res;
}

extern "C" bool Die_y_pos_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> Die_y_pos_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	ref<Expr> res = ConstantExpr::create(0x0002, w);
	return res;
}


extern "C" bool ADC12_offset_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> ADC12_offset_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"ADC12_offset_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}
extern "C" bool REF_15reference_factor_w(ExecutionState* s, uint64_t addr, ref<Expr> v){
	std::cerr << "writing to " << __PRETTY_FUNCTION__ << "\n";
	return true;
}

extern "C" ref<Expr> REF_15reference_factor_r(ExecutionState* s, uint64_t addr, Expr::Width w){
	static unsigned int use_count;
	std::cerr << "reading from " << __PRETTY_FUNCTION__ << "\n";
	const Array * array = new Array(
		"REF_15reference_factor_arr" + llvm::utostr(++use_count), w);
	ref<Expr> res = Expr::createTempRead(array, w, true);
	return res;
}