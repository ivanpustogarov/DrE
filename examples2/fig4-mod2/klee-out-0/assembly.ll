; ModuleID = 'main.bc'
target datalayout = "e-p:16:16:16-i8:8:8-i16:16:16-i32:16:32-n8:16"
target triple = "msp430"

@adc = global i16 0, align 2
@.str = private unnamed_addr constant [5 x i8] c"mode\00", align 1
@num_of_adc_reads = global i16 0, align 2
@llvm.used = appending global [1 x i8*] [i8* bitcast (void ()* @ADC10_ISR to i8*)], section "llvm.metadata"
@.str1 = private unnamed_addr constant [22 x i8] c"klee_div_zero_check.c\00", align 1
@.str12 = private unnamed_addr constant [15 x i8] c"divide by zero\00", align 1
@.str2 = private unnamed_addr constant [8 x i8] c"div.err\00", align 1
@.str3 = private unnamed_addr constant [8 x i8] c"IGNORED\00", align 1
@.str14 = private unnamed_addr constant [16 x i8] c"overshift error\00", align 1
@.str25 = private unnamed_addr constant [14 x i8] c"overshift.err\00", align 1
@.str6 = private unnamed_addr constant [13 x i8] c"klee_range.c\00", align 1
@.str17 = private unnamed_addr constant [14 x i8] c"invalid range\00", align 1
@.str28 = private unnamed_addr constant [5 x i8] c"user\00", align 1

@__isr_5 = alias void ()* @ADC10_ISR

; Function Attrs: nounwind
define i16 @get_acceleration(i16 %mode) #0 {
entry:
  %retval = alloca i16, align 2
  %mode.addr = alloca i16, align 2
  %i = alloca i16, align 2
  store i16 %mode, i16* %mode.addr, align 2
  store i16 0, i16* %i, align 2, !dbg !138
  %call = call i16 bitcast (i16 (...)* @__bis_SR_register to i16 (i16)*)(i16 24), !dbg !139
  br label %while.cond, !dbg !140

while.cond:                                       ; preds = %while.body, %entry
  %0 = load i16* @adc, align 2, !dbg !140
  %cmp = icmp sge i16 %0, 15, !dbg !140
  %1 = load i16* %i, align 2, !dbg !141
  br i1 %cmp, label %while.body, label %while.end, !dbg !140

while.body:                                       ; preds = %while.cond
  %inc = add nsw i16 %1, 1, !dbg !141
  store i16 %inc, i16* %i, align 2, !dbg !141
  %call1 = call i16 bitcast (i16 (...)* @__bis_SR_register to i16 (i16)*)(i16 24), !dbg !143
  br label %while.cond, !dbg !144

while.end:                                        ; preds = %while.cond
  %cmp2 = icmp sgt i16 %1, 15, !dbg !145
  %2 = load i16* %mode.addr, align 2, !dbg !145
  %cmp3 = icmp eq i16 %2, 97, !dbg !145
  %or.cond = and i1 %cmp2, %cmp3, !dbg !145
  br i1 %or.cond, label %if.then, label %if.else, !dbg !145

if.then:                                          ; preds = %while.end
  store i16 1, i16* %retval, !dbg !147
  br label %return, !dbg !147

if.else:                                          ; preds = %while.end
  %3 = load i16* %mode.addr, align 2, !dbg !148
  %cmp4 = icmp eq i16 %3, 97, !dbg !148
  br i1 %cmp4, label %if.then5, label %if.else6, !dbg !148

if.then5:                                         ; preds = %if.else
  store i16 2, i16* %retval, !dbg !150
  br label %return, !dbg !150

if.else6:                                         ; preds = %if.else
  store i16 3, i16* %retval, !dbg !151
  br label %return, !dbg !151

return:                                           ; preds = %if.else6, %if.then5, %if.then
  %4 = load i16* %retval, !dbg !152
  ret i16 %4, !dbg !152
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata) #1

declare i16 @__bis_SR_register(...) #2

; Function Attrs: nounwind
define i16 @main() #0 {
entry:
  %retval = alloca i16, align 2
  %val = alloca i16, align 2
  %val_repv = alloca i16, align 2
  %tick = alloca i16, align 2
  %acceleration = alloca [3 x i16], align 2
  %j = alloca i16, align 2
  %mode = alloca i16, align 2
  store i16 0, i16* %retval
  store i16 0, i16* %val, align 2, !dbg !153
  store i16 0, i16* %val_repv, align 2, !dbg !153
  store i16 0, i16* %tick, align 2, !dbg !154
  %0 = bitcast [3 x i16]* %acceleration to i8*, !dbg !155
  %1 = call i8* bitcast (i8* (i8*, i32, i64)* @memset to i8* (i8*, i32, i16)*)(i8* %0, i32 0, i16 6)
  store i16 0, i16* %j, align 2, !dbg !156
  %call = call i16 bitcast (i16 (...)* @klee_make_symbolic to i16 (i16*, i16, i8*)*)(i16* %mode, i16 2, i8* getelementptr inbounds ([5 x i8]* @.str, i32 0, i32 0)), !dbg !157
  br label %while.body, !dbg !158

while.body:                                       ; preds = %while.body, %land.lhs.true, %land.lhs.true6, %entry
  %2 = load i16* %mode, align 2, !dbg !159
  %call1 = call i16 @get_acceleration(i16 %2), !dbg !159
  %3 = load i16* %j, align 2, !dbg !159
  %arrayidx = getelementptr inbounds [3 x i16]* %acceleration, i32 0, i16 %3, !dbg !159
  store i16 %call1, i16* %arrayidx, align 2, !dbg !159
  %4 = load i16* %j, align 2, !dbg !161
  %inc = add nsw i16 %4, 1, !dbg !161
  store i16 %inc, i16* %j, align 2, !dbg !161
  %5 = load i16* %j, align 2, !dbg !162
  %cmp = icmp eq i16 %5, 3, !dbg !162
  %.inc = select i1 %cmp, i16 0, i16 %inc, !dbg !162
  store i16 %.inc, i16* %j, align 2, !dbg !162
  %arrayidx2 = getelementptr inbounds [3 x i16]* %acceleration, i32 0, i16 0, !dbg !164
  %6 = load i16* %arrayidx2, align 2, !dbg !164
  %cmp3 = icmp eq i16 %6, 1, !dbg !164
  br i1 %cmp3, label %land.lhs.true, label %while.body, !dbg !164

land.lhs.true:                                    ; preds = %while.body
  %arrayidx4 = getelementptr inbounds [3 x i16]* %acceleration, i32 0, i16 1, !dbg !164
  %7 = load i16* %arrayidx4, align 2, !dbg !164
  %cmp5 = icmp eq i16 %7, 1, !dbg !164
  br i1 %cmp5, label %land.lhs.true6, label %while.body, !dbg !164

land.lhs.true6:                                   ; preds = %land.lhs.true
  %arrayidx7 = getelementptr inbounds [3 x i16]* %acceleration, i32 0, i16 2, !dbg !164
  %8 = load i16* %arrayidx7, align 2, !dbg !164
  %cmp8 = icmp eq i16 %8, 1, !dbg !164
  br i1 %cmp8, label %while.end, label %while.body, !dbg !164

while.end:                                        ; preds = %land.lhs.true6
  %call11 = call i16 @assert(i16 0), !dbg !166
  ret i16 0, !dbg !167
}

; Function Attrs: nounwind
declare void @llvm.memset.p0i8.i16(i8* nocapture, i8, i16, i32, i1) #3

declare i16 @klee_make_symbolic(...) #2

declare i16 @assert(i16) #2

; Function Attrs: noinline nounwind
define msp430_intrcc void @ADC10_ISR() #4 {
entry:
  %0 = load volatile i16* inttoptr (i16 436 to i16*), align 2, !dbg !168
  store i16 %0, i16* @adc, align 2, !dbg !168
  %1 = load i16* @num_of_adc_reads, align 2, !dbg !169
  %inc = add nsw i16 %1, 1, !dbg !169
  store i16 %inc, i16* @num_of_adc_reads, align 2, !dbg !169
  %call = call i16 bitcast (i16 (...)* @__bic_SR_register_on_exit to i16 (i16)*)(i16 16), !dbg !170
  ret void, !dbg !171
}

declare i16 @__bic_SR_register_on_exit(...) #2

; Function Attrs: nounwind uwtable
define void @klee_div_zero_check(i64 %z) #5 {
entry:
  %cmp = icmp eq i64 %z, 0, !dbg !172
  br i1 %cmp, label %if.then, label %if.end, !dbg !172

if.then:                                          ; preds = %entry
  tail call void @klee_report_error(i8* getelementptr inbounds ([22 x i8]* @.str1, i64 0, i64 0), i32 14, i8* getelementptr inbounds ([15 x i8]* @.str12, i64 0, i64 0), i8* getelementptr inbounds ([8 x i8]* @.str2, i64 0, i64 0)) #8, !dbg !174
  unreachable, !dbg !174

if.end:                                           ; preds = %entry
  ret void, !dbg !175
}

; Function Attrs: noreturn
declare void @klee_report_error(i8*, i32, i8*, i8*) #6

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @klee_int(i8* %name) #5 {
entry:
  %x = alloca i32, align 4
  %0 = bitcast i32* %x to i8*, !dbg !176
  call void bitcast (i16 (...)* @klee_make_symbolic to void (i8*, i64, i8*)*)(i8* %0, i64 4, i8* %name) #9, !dbg !176
  %1 = load i32* %x, align 4, !dbg !177, !tbaa !178
  ret i32 %1, !dbg !177
}

; Function Attrs: nounwind uwtable
define void @klee_overshift_check(i64 %bitWidth, i64 %shift) #5 {
entry:
  %cmp = icmp ult i64 %shift, %bitWidth, !dbg !182
  br i1 %cmp, label %if.end, label %if.then, !dbg !182

if.then:                                          ; preds = %entry
  tail call void @klee_report_error(i8* getelementptr inbounds ([8 x i8]* @.str3, i64 0, i64 0), i32 0, i8* getelementptr inbounds ([16 x i8]* @.str14, i64 0, i64 0), i8* getelementptr inbounds ([14 x i8]* @.str25, i64 0, i64 0)) #8, !dbg !184
  unreachable, !dbg !184

if.end:                                           ; preds = %entry
  ret void, !dbg !186
}

; Function Attrs: nounwind uwtable
define i32 @klee_range(i32 %start, i32 %end, i8* %name) #5 {
entry:
  %x = alloca i32, align 4
  %cmp = icmp slt i32 %start, %end, !dbg !187
  br i1 %cmp, label %if.end, label %if.then, !dbg !187

if.then:                                          ; preds = %entry
  call void @klee_report_error(i8* getelementptr inbounds ([13 x i8]* @.str6, i64 0, i64 0), i32 17, i8* getelementptr inbounds ([14 x i8]* @.str17, i64 0, i64 0), i8* getelementptr inbounds ([5 x i8]* @.str28, i64 0, i64 0)) #8, !dbg !189
  unreachable, !dbg !189

if.end:                                           ; preds = %entry
  %add = add nsw i32 %start, 1, !dbg !190
  %cmp1 = icmp eq i32 %add, %end, !dbg !190
  br i1 %cmp1, label %return, label %if.else, !dbg !190

if.else:                                          ; preds = %if.end
  %0 = bitcast i32* %x to i8*, !dbg !192
  call void bitcast (i16 (...)* @klee_make_symbolic to void (i8*, i64, i8*)*)(i8* %0, i64 4, i8* %name) #9, !dbg !192
  %cmp3 = icmp eq i32 %start, 0, !dbg !194
  %1 = load i32* %x, align 4, !dbg !196, !tbaa !178
  br i1 %cmp3, label %if.then4, label %if.else7, !dbg !194

if.then4:                                         ; preds = %if.else
  %cmp5 = icmp ult i32 %1, %end, !dbg !196
  %conv6 = zext i1 %cmp5 to i64, !dbg !196
  call void @klee_assume(i64 %conv6) #9, !dbg !196
  br label %if.end14, !dbg !198

if.else7:                                         ; preds = %if.else
  %cmp8 = icmp sge i32 %1, %start, !dbg !199
  %conv10 = zext i1 %cmp8 to i64, !dbg !199
  call void @klee_assume(i64 %conv10) #9, !dbg !199
  %2 = load i32* %x, align 4, !dbg !201, !tbaa !178
  %cmp11 = icmp slt i32 %2, %end, !dbg !201
  %conv13 = zext i1 %cmp11 to i64, !dbg !201
  call void @klee_assume(i64 %conv13) #9, !dbg !201
  br label %if.end14

if.end14:                                         ; preds = %if.else7, %if.then4
  %3 = load i32* %x, align 4, !dbg !202, !tbaa !178
  br label %return, !dbg !202

return:                                           ; preds = %if.end14, %if.end
  %retval.0 = phi i32 [ %3, %if.end14 ], [ %start, %if.end ]
  ret i32 %retval.0, !dbg !203
}

declare void @klee_assume(i64) #7

; Function Attrs: nounwind uwtable
define weak i8* @memcpy(i8* %destaddr, i8* %srcaddr, i64 %len) #5 {
entry:
  %cmp3 = icmp eq i64 %len, 0, !dbg !204
  br i1 %cmp3, label %while.end, label %while.body.preheader, !dbg !204

while.body.preheader:                             ; preds = %entry
  %n.vec = and i64 %len, -32
  %cmp.zero = icmp eq i64 %n.vec, 0
  %0 = add i64 %len, -1
  br i1 %cmp.zero, label %middle.block, label %vector.memcheck

vector.memcheck:                                  ; preds = %while.body.preheader
  %scevgep7 = getelementptr i8* %srcaddr, i64 %0
  %scevgep = getelementptr i8* %destaddr, i64 %0
  %bound1 = icmp uge i8* %scevgep, %srcaddr
  %bound0 = icmp uge i8* %scevgep7, %destaddr
  %memcheck.conflict = and i1 %bound0, %bound1
  %ptr.ind.end = getelementptr i8* %srcaddr, i64 %n.vec
  %ptr.ind.end9 = getelementptr i8* %destaddr, i64 %n.vec
  %rev.ind.end = sub i64 %len, %n.vec
  br i1 %memcheck.conflict, label %middle.block, label %vector.body

vector.body:                                      ; preds = %vector.body, %vector.memcheck
  %index = phi i64 [ %index.next, %vector.body ], [ 0, %vector.memcheck ]
  %next.gep = getelementptr i8* %srcaddr, i64 %index
  %next.gep106 = getelementptr i8* %destaddr, i64 %index
  %1 = bitcast i8* %next.gep to <16 x i8>*, !dbg !205
  %wide.load = load <16 x i8>* %1, align 1, !dbg !205
  %next.gep.sum282 = or i64 %index, 16, !dbg !205
  %2 = getelementptr i8* %srcaddr, i64 %next.gep.sum282, !dbg !205
  %3 = bitcast i8* %2 to <16 x i8>*, !dbg !205
  %wide.load203 = load <16 x i8>* %3, align 1, !dbg !205
  %4 = bitcast i8* %next.gep106 to <16 x i8>*, !dbg !205
  store <16 x i8> %wide.load, <16 x i8>* %4, align 1, !dbg !205
  %5 = getelementptr i8* %destaddr, i64 %next.gep.sum282, !dbg !205
  %6 = bitcast i8* %5 to <16 x i8>*, !dbg !205
  store <16 x i8> %wide.load203, <16 x i8>* %6, align 1, !dbg !205
  %index.next = add i64 %index, 32
  %7 = icmp eq i64 %index.next, %n.vec
  br i1 %7, label %middle.block, label %vector.body, !llvm.loop !206

middle.block:                                     ; preds = %vector.body, %vector.memcheck, %while.body.preheader
  %resume.val = phi i8* [ %srcaddr, %while.body.preheader ], [ %srcaddr, %vector.memcheck ], [ %ptr.ind.end, %vector.body ]
  %resume.val8 = phi i8* [ %destaddr, %while.body.preheader ], [ %destaddr, %vector.memcheck ], [ %ptr.ind.end9, %vector.body ]
  %resume.val10 = phi i64 [ %len, %while.body.preheader ], [ %len, %vector.memcheck ], [ %rev.ind.end, %vector.body ]
  %new.indc.resume.val = phi i64 [ 0, %while.body.preheader ], [ 0, %vector.memcheck ], [ %n.vec, %vector.body ]
  %cmp.n = icmp eq i64 %new.indc.resume.val, %len
  br i1 %cmp.n, label %while.end, label %while.body

while.body:                                       ; preds = %while.body, %middle.block
  %src.06 = phi i8* [ %incdec.ptr, %while.body ], [ %resume.val, %middle.block ]
  %dest.05 = phi i8* [ %incdec.ptr1, %while.body ], [ %resume.val8, %middle.block ]
  %len.addr.04 = phi i64 [ %dec, %while.body ], [ %resume.val10, %middle.block ]
  %dec = add i64 %len.addr.04, -1, !dbg !204
  %incdec.ptr = getelementptr inbounds i8* %src.06, i64 1, !dbg !205
  %8 = load i8* %src.06, align 1, !dbg !205, !tbaa !209
  %incdec.ptr1 = getelementptr inbounds i8* %dest.05, i64 1, !dbg !205
  store i8 %8, i8* %dest.05, align 1, !dbg !205, !tbaa !209
  %cmp = icmp eq i64 %dec, 0, !dbg !204
  br i1 %cmp, label %while.end, label %while.body, !dbg !204, !llvm.loop !210

while.end:                                        ; preds = %while.body, %middle.block, %entry
  ret i8* %destaddr, !dbg !211
}

; Function Attrs: nounwind uwtable
define weak i8* @memmove(i8* %dst, i8* %src, i64 %count) #5 {
entry:
  %cmp = icmp eq i8* %src, %dst, !dbg !212
  br i1 %cmp, label %return, label %if.end, !dbg !212

if.end:                                           ; preds = %entry
  %cmp1 = icmp ugt i8* %src, %dst, !dbg !214
  br i1 %cmp1, label %while.cond.preheader, label %if.else, !dbg !214

while.cond.preheader:                             ; preds = %if.end
  %tobool27 = icmp eq i64 %count, 0, !dbg !216
  br i1 %tobool27, label %return, label %while.body.preheader, !dbg !216

while.body.preheader:                             ; preds = %while.cond.preheader
  %n.vec = and i64 %count, -32
  %cmp.zero = icmp eq i64 %n.vec, 0
  %0 = add i64 %count, -1
  br i1 %cmp.zero, label %middle.block, label %vector.memcheck

vector.memcheck:                                  ; preds = %while.body.preheader
  %scevgep37 = getelementptr i8* %src, i64 %0
  %scevgep = getelementptr i8* %dst, i64 %0
  %bound1 = icmp uge i8* %scevgep, %src
  %bound0 = icmp uge i8* %scevgep37, %dst
  %memcheck.conflict = and i1 %bound0, %bound1
  %ptr.ind.end = getelementptr i8* %src, i64 %n.vec
  %ptr.ind.end39 = getelementptr i8* %dst, i64 %n.vec
  %rev.ind.end = sub i64 %count, %n.vec
  br i1 %memcheck.conflict, label %middle.block, label %vector.body

vector.body:                                      ; preds = %vector.body, %vector.memcheck
  %index = phi i64 [ %index.next, %vector.body ], [ 0, %vector.memcheck ]
  %next.gep = getelementptr i8* %src, i64 %index
  %next.gep136 = getelementptr i8* %dst, i64 %index
  %1 = bitcast i8* %next.gep to <16 x i8>*, !dbg !216
  %wide.load = load <16 x i8>* %1, align 1, !dbg !216
  %next.gep.sum610 = or i64 %index, 16, !dbg !216
  %2 = getelementptr i8* %src, i64 %next.gep.sum610, !dbg !216
  %3 = bitcast i8* %2 to <16 x i8>*, !dbg !216
  %wide.load233 = load <16 x i8>* %3, align 1, !dbg !216
  %4 = bitcast i8* %next.gep136 to <16 x i8>*, !dbg !216
  store <16 x i8> %wide.load, <16 x i8>* %4, align 1, !dbg !216
  %5 = getelementptr i8* %dst, i64 %next.gep.sum610, !dbg !216
  %6 = bitcast i8* %5 to <16 x i8>*, !dbg !216
  store <16 x i8> %wide.load233, <16 x i8>* %6, align 1, !dbg !216
  %index.next = add i64 %index, 32
  %7 = icmp eq i64 %index.next, %n.vec
  br i1 %7, label %middle.block, label %vector.body, !llvm.loop !218

middle.block:                                     ; preds = %vector.body, %vector.memcheck, %while.body.preheader
  %resume.val = phi i8* [ %src, %while.body.preheader ], [ %src, %vector.memcheck ], [ %ptr.ind.end, %vector.body ]
  %resume.val38 = phi i8* [ %dst, %while.body.preheader ], [ %dst, %vector.memcheck ], [ %ptr.ind.end39, %vector.body ]
  %resume.val40 = phi i64 [ %count, %while.body.preheader ], [ %count, %vector.memcheck ], [ %rev.ind.end, %vector.body ]
  %new.indc.resume.val = phi i64 [ 0, %while.body.preheader ], [ 0, %vector.memcheck ], [ %n.vec, %vector.body ]
  %cmp.n = icmp eq i64 %new.indc.resume.val, %count
  br i1 %cmp.n, label %return, label %while.body

while.body:                                       ; preds = %while.body, %middle.block
  %b.030 = phi i8* [ %incdec.ptr, %while.body ], [ %resume.val, %middle.block ]
  %a.029 = phi i8* [ %incdec.ptr3, %while.body ], [ %resume.val38, %middle.block ]
  %count.addr.028 = phi i64 [ %dec, %while.body ], [ %resume.val40, %middle.block ]
  %dec = add i64 %count.addr.028, -1, !dbg !216
  %incdec.ptr = getelementptr inbounds i8* %b.030, i64 1, !dbg !216
  %8 = load i8* %b.030, align 1, !dbg !216, !tbaa !209
  %incdec.ptr3 = getelementptr inbounds i8* %a.029, i64 1, !dbg !216
  store i8 %8, i8* %a.029, align 1, !dbg !216, !tbaa !209
  %tobool = icmp eq i64 %dec, 0, !dbg !216
  br i1 %tobool, label %return, label %while.body, !dbg !216, !llvm.loop !219

if.else:                                          ; preds = %if.end
  %sub = add i64 %count, -1, !dbg !220
  %tobool832 = icmp eq i64 %count, 0, !dbg !222
  br i1 %tobool832, label %return, label %while.body9.lr.ph, !dbg !222

while.body9.lr.ph:                                ; preds = %if.else
  %add.ptr5 = getelementptr inbounds i8* %src, i64 %sub, !dbg !223
  %add.ptr = getelementptr inbounds i8* %dst, i64 %sub, !dbg !220
  %n.vec241 = and i64 %count, -32
  %cmp.zero243 = icmp eq i64 %n.vec241, 0
  br i1 %cmp.zero243, label %middle.block236, label %vector.memcheck250

vector.memcheck250:                               ; preds = %while.body9.lr.ph
  %bound1247 = icmp ule i8* %add.ptr5, %dst
  %bound0246 = icmp ule i8* %add.ptr, %src
  %memcheck.conflict249 = and i1 %bound0246, %bound1247
  %add.ptr5.sum = sub i64 %sub, %n.vec241
  %rev.ptr.ind.end = getelementptr i8* %src, i64 %add.ptr5.sum
  %rev.ptr.ind.end255 = getelementptr i8* %dst, i64 %add.ptr5.sum
  %rev.ind.end257 = sub i64 %count, %n.vec241
  br i1 %memcheck.conflict249, label %middle.block236, label %vector.body235

vector.body235:                                   ; preds = %vector.body235, %vector.memcheck250
  %index238 = phi i64 [ %index.next260, %vector.body235 ], [ 0, %vector.memcheck250 ]
  %add.ptr5.sum465 = sub i64 %sub, %index238
  %next.gep262.sum = add i64 %add.ptr5.sum465, -15, !dbg !222
  %9 = getelementptr i8* %src, i64 %next.gep262.sum, !dbg !222
  %10 = bitcast i8* %9 to <16 x i8>*, !dbg !222
  %wide.load460 = load <16 x i8>* %10, align 1, !dbg !222
  %reverse = shufflevector <16 x i8> %wide.load460, <16 x i8> undef, <16 x i32> <i32 15, i32 14, i32 13, i32 12, i32 11, i32 10, i32 9, i32 8, i32 7, i32 6, i32 5, i32 4, i32 3, i32 2, i32 1, i32 0>, !dbg !222
  %.sum = add i64 %add.ptr5.sum465, -31, !dbg !222
  %11 = getelementptr i8* %src, i64 %.sum, !dbg !222
  %12 = bitcast i8* %11 to <16 x i8>*, !dbg !222
  %wide.load461 = load <16 x i8>* %12, align 1, !dbg !222
  %reverse462 = shufflevector <16 x i8> %wide.load461, <16 x i8> undef, <16 x i32> <i32 15, i32 14, i32 13, i32 12, i32 11, i32 10, i32 9, i32 8, i32 7, i32 6, i32 5, i32 4, i32 3, i32 2, i32 1, i32 0>, !dbg !222
  %reverse463 = shufflevector <16 x i8> %reverse, <16 x i8> undef, <16 x i32> <i32 15, i32 14, i32 13, i32 12, i32 11, i32 10, i32 9, i32 8, i32 7, i32 6, i32 5, i32 4, i32 3, i32 2, i32 1, i32 0>, !dbg !222
  %13 = getelementptr i8* %dst, i64 %next.gep262.sum, !dbg !222
  %14 = bitcast i8* %13 to <16 x i8>*, !dbg !222
  store <16 x i8> %reverse463, <16 x i8>* %14, align 1, !dbg !222
  %reverse464 = shufflevector <16 x i8> %reverse462, <16 x i8> undef, <16 x i32> <i32 15, i32 14, i32 13, i32 12, i32 11, i32 10, i32 9, i32 8, i32 7, i32 6, i32 5, i32 4, i32 3, i32 2, i32 1, i32 0>, !dbg !222
  %15 = getelementptr i8* %dst, i64 %.sum, !dbg !222
  %16 = bitcast i8* %15 to <16 x i8>*, !dbg !222
  store <16 x i8> %reverse464, <16 x i8>* %16, align 1, !dbg !222
  %index.next260 = add i64 %index238, 32
  %17 = icmp eq i64 %index.next260, %n.vec241
  br i1 %17, label %middle.block236, label %vector.body235, !llvm.loop !224

middle.block236:                                  ; preds = %vector.body235, %vector.memcheck250, %while.body9.lr.ph
  %resume.val251 = phi i8* [ %add.ptr5, %while.body9.lr.ph ], [ %add.ptr5, %vector.memcheck250 ], [ %rev.ptr.ind.end, %vector.body235 ]
  %resume.val253 = phi i8* [ %add.ptr, %while.body9.lr.ph ], [ %add.ptr, %vector.memcheck250 ], [ %rev.ptr.ind.end255, %vector.body235 ]
  %resume.val256 = phi i64 [ %count, %while.body9.lr.ph ], [ %count, %vector.memcheck250 ], [ %rev.ind.end257, %vector.body235 ]
  %new.indc.resume.val258 = phi i64 [ 0, %while.body9.lr.ph ], [ 0, %vector.memcheck250 ], [ %n.vec241, %vector.body235 ]
  %cmp.n259 = icmp eq i64 %new.indc.resume.val258, %count
  br i1 %cmp.n259, label %return, label %while.body9

while.body9:                                      ; preds = %while.body9, %middle.block236
  %b.135 = phi i8* [ %incdec.ptr10, %while.body9 ], [ %resume.val251, %middle.block236 ]
  %a.134 = phi i8* [ %incdec.ptr11, %while.body9 ], [ %resume.val253, %middle.block236 ]
  %count.addr.133 = phi i64 [ %dec7, %while.body9 ], [ %resume.val256, %middle.block236 ]
  %dec7 = add i64 %count.addr.133, -1, !dbg !222
  %incdec.ptr10 = getelementptr inbounds i8* %b.135, i64 -1, !dbg !222
  %18 = load i8* %b.135, align 1, !dbg !222, !tbaa !209
  %incdec.ptr11 = getelementptr inbounds i8* %a.134, i64 -1, !dbg !222
  store i8 %18, i8* %a.134, align 1, !dbg !222, !tbaa !209
  %tobool8 = icmp eq i64 %dec7, 0, !dbg !222
  br i1 %tobool8, label %return, label %while.body9, !dbg !222, !llvm.loop !225

return:                                           ; preds = %while.body9, %middle.block236, %if.else, %while.body, %middle.block, %while.cond.preheader, %entry
  ret i8* %dst, !dbg !226
}

; Function Attrs: nounwind uwtable
define weak i8* @mempcpy(i8* %destaddr, i8* %srcaddr, i64 %len) #5 {
entry:
  %cmp3 = icmp eq i64 %len, 0, !dbg !227
  br i1 %cmp3, label %while.end, label %while.body.preheader, !dbg !227

while.body.preheader:                             ; preds = %entry
  %n.vec = and i64 %len, -32
  %cmp.zero = icmp eq i64 %n.vec, 0
  %0 = add i64 %len, -1
  br i1 %cmp.zero, label %middle.block, label %vector.memcheck

vector.memcheck:                                  ; preds = %while.body.preheader
  %scevgep8 = getelementptr i8* %srcaddr, i64 %0
  %scevgep7 = getelementptr i8* %destaddr, i64 %0
  %bound1 = icmp uge i8* %scevgep7, %srcaddr
  %bound0 = icmp uge i8* %scevgep8, %destaddr
  %memcheck.conflict = and i1 %bound0, %bound1
  %ptr.ind.end = getelementptr i8* %srcaddr, i64 %n.vec
  %ptr.ind.end10 = getelementptr i8* %destaddr, i64 %n.vec
  %rev.ind.end = sub i64 %len, %n.vec
  br i1 %memcheck.conflict, label %middle.block, label %vector.body

vector.body:                                      ; preds = %vector.body, %vector.memcheck
  %index = phi i64 [ %index.next, %vector.body ], [ 0, %vector.memcheck ]
  %next.gep = getelementptr i8* %srcaddr, i64 %index
  %next.gep107 = getelementptr i8* %destaddr, i64 %index
  %1 = bitcast i8* %next.gep to <16 x i8>*, !dbg !228
  %wide.load = load <16 x i8>* %1, align 1, !dbg !228
  %next.gep.sum283 = or i64 %index, 16, !dbg !228
  %2 = getelementptr i8* %srcaddr, i64 %next.gep.sum283, !dbg !228
  %3 = bitcast i8* %2 to <16 x i8>*, !dbg !228
  %wide.load204 = load <16 x i8>* %3, align 1, !dbg !228
  %4 = bitcast i8* %next.gep107 to <16 x i8>*, !dbg !228
  store <16 x i8> %wide.load, <16 x i8>* %4, align 1, !dbg !228
  %5 = getelementptr i8* %destaddr, i64 %next.gep.sum283, !dbg !228
  %6 = bitcast i8* %5 to <16 x i8>*, !dbg !228
  store <16 x i8> %wide.load204, <16 x i8>* %6, align 1, !dbg !228
  %index.next = add i64 %index, 32
  %7 = icmp eq i64 %index.next, %n.vec
  br i1 %7, label %middle.block, label %vector.body, !llvm.loop !229

middle.block:                                     ; preds = %vector.body, %vector.memcheck, %while.body.preheader
  %resume.val = phi i8* [ %srcaddr, %while.body.preheader ], [ %srcaddr, %vector.memcheck ], [ %ptr.ind.end, %vector.body ]
  %resume.val9 = phi i8* [ %destaddr, %while.body.preheader ], [ %destaddr, %vector.memcheck ], [ %ptr.ind.end10, %vector.body ]
  %resume.val11 = phi i64 [ %len, %while.body.preheader ], [ %len, %vector.memcheck ], [ %rev.ind.end, %vector.body ]
  %new.indc.resume.val = phi i64 [ 0, %while.body.preheader ], [ 0, %vector.memcheck ], [ %n.vec, %vector.body ]
  %cmp.n = icmp eq i64 %new.indc.resume.val, %len
  br i1 %cmp.n, label %while.cond.while.end_crit_edge, label %while.body

while.body:                                       ; preds = %while.body, %middle.block
  %src.06 = phi i8* [ %incdec.ptr, %while.body ], [ %resume.val, %middle.block ]
  %dest.05 = phi i8* [ %incdec.ptr1, %while.body ], [ %resume.val9, %middle.block ]
  %len.addr.04 = phi i64 [ %dec, %while.body ], [ %resume.val11, %middle.block ]
  %dec = add i64 %len.addr.04, -1, !dbg !227
  %incdec.ptr = getelementptr inbounds i8* %src.06, i64 1, !dbg !228
  %8 = load i8* %src.06, align 1, !dbg !228, !tbaa !209
  %incdec.ptr1 = getelementptr inbounds i8* %dest.05, i64 1, !dbg !228
  store i8 %8, i8* %dest.05, align 1, !dbg !228, !tbaa !209
  %cmp = icmp eq i64 %dec, 0, !dbg !227
  br i1 %cmp, label %while.cond.while.end_crit_edge, label %while.body, !dbg !227, !llvm.loop !230

while.cond.while.end_crit_edge:                   ; preds = %while.body, %middle.block
  %scevgep = getelementptr i8* %destaddr, i64 %len
  br label %while.end, !dbg !227

while.end:                                        ; preds = %while.cond.while.end_crit_edge, %entry
  %dest.0.lcssa = phi i8* [ %scevgep, %while.cond.while.end_crit_edge ], [ %destaddr, %entry ]
  ret i8* %dest.0.lcssa, !dbg !231
}

; Function Attrs: nounwind uwtable
define weak i8* @memset(i8* %dst, i32 %s, i64 %count) #5 {
entry:
  %cmp2 = icmp eq i64 %count, 0, !dbg !232
  br i1 %cmp2, label %while.end, label %while.body.lr.ph, !dbg !232

while.body.lr.ph:                                 ; preds = %entry
  %conv = trunc i32 %s to i8, !dbg !233
  br label %while.body, !dbg !232

while.body:                                       ; preds = %while.body, %while.body.lr.ph
  %a.04 = phi i8* [ %dst, %while.body.lr.ph ], [ %incdec.ptr, %while.body ]
  %count.addr.03 = phi i64 [ %count, %while.body.lr.ph ], [ %dec, %while.body ]
  %dec = add i64 %count.addr.03, -1, !dbg !232
  %incdec.ptr = getelementptr inbounds i8* %a.04, i64 1, !dbg !233
  store volatile i8 %conv, i8* %a.04, align 1, !dbg !233, !tbaa !209
  %cmp = icmp eq i64 %dec, 0, !dbg !232
  br i1 %cmp, label %while.end, label %while.body, !dbg !232

while.end:                                        ; preds = %while.body, %entry
  ret i8* %dst, !dbg !234
}

attributes #0 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false
attributes #1 = { nounwind readnone }
attributes #2 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }
attributes #4 = { noinline nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-floa
attributes #5 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { noreturn "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { nobuiltin noreturn nounwind }
attributes #9 = { nobuiltin nounwind }

!llvm.dbg.cu = !{!0, !18, !29, !44, !56, !69, !89, !104, !119}
!llvm.module.flags = !{!135, !136}
!llvm.ident = !{!137, !137, !137, !137, !137, !137, !137, !137, !137}

!0 = metadata !{i32 786449, metadata !1, i32 12, metadata !"clang version 3.4.2 (tags/RELEASE_34/dot2-final)", i1 false, metadata !"", i32 0, metadata !2, metadata !2, metadata !3, metadata !15, metadata !2, metadata !""} ; [ DW_TAG_compile_unit ] [/home
!1 = metadata !{metadata !"main.c", metadata !"/home/ivan/Workspaces/DrE/examples2/fig4-mod2"}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4, metadata !9, metadata !12}
!4 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"get_acceleration", metadata !"get_acceleration", metadata !"", i32 6, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 false, i16 (i16)* @get_acceleration, null, null, metada
!5 = metadata !{i32 786473, metadata !1}          ; [ DW_TAG_file_type ] [/home/ivan/Workspaces/DrE/examples2/fig4-mod2/main.c]
!6 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !7, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!7 = metadata !{metadata !8, metadata !8}
!8 = metadata !{i32 786468, null, null, metadata !"int", i32 0, i64 16, i64 16, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ] [int] [line 0, size 16, align 16, offset 0, enc DW_ATE_signed]
!9 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"main", metadata !"main", metadata !"", i32 29, metadata !10, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i16 ()* @main, null, null, metadata !2, i32 30} ; [ DW_TAG_subprogram ] 
!10 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !11, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!11 = metadata !{metadata !8}
!12 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"ADC10_ISR", metadata !"ADC10_ISR", metadata !"", i32 56, metadata !13, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 false, void ()* @ADC10_ISR, null, null, metadata !2, i32 60} ; [ D
!13 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !14, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!14 = metadata !{null}
!15 = metadata !{metadata !16, metadata !17}
!16 = metadata !{i32 786484, i32 0, null, metadata !"adc", metadata !"adc", metadata !"", metadata !5, i32 4, metadata !8, i32 0, i32 1, i16* @adc, null} ; [ DW_TAG_variable ] [adc] [line 4] [def]
!17 = metadata !{i32 786484, i32 0, null, metadata !"num_of_adc_reads", metadata !"num_of_adc_reads", metadata !"", metadata !5, i32 51, metadata !8, i32 0, i32 1, i16* @num_of_adc_reads, null} ; [ DW_TAG_variable ] [num_of_adc_reads] [line 51] [def]
!18 = metadata !{i32 786449, metadata !19, i32 1, metadata !"clang version 3.4.2 (tags/RELEASE_34/dot2-final)", i1 true, metadata !"", i32 0, metadata !2, metadata !2, metadata !20, metadata !2, metadata !2, metadata !""} ; [ DW_TAG_compile_unit ] [/home
!19 = metadata !{metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic/klee_div_zero_check.c", metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic"}
!20 = metadata !{metadata !21}
!21 = metadata !{i32 786478, metadata !22, metadata !23, metadata !"klee_div_zero_check", metadata !"klee_div_zero_check", metadata !"", i32 12, metadata !24, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 true, void (i64)* @klee_div_zero_check, null
!22 = metadata !{metadata !"klee_div_zero_check.c", metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic"}
!23 = metadata !{i32 786473, metadata !22}        ; [ DW_TAG_file_type ] [/home/ivan/Workspaces/DrE/runtime/Intrinsic/klee_div_zero_check.c]
!24 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !25, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!25 = metadata !{null, metadata !26}
!26 = metadata !{i32 786468, null, null, metadata !"long long int", i32 0, i64 64, i64 64, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ] [long long int] [line 0, size 64, align 64, offset 0, enc DW_ATE_signed]
!27 = metadata !{metadata !28}
!28 = metadata !{i32 786689, metadata !21, metadata !"z", metadata !23, i32 16777228, metadata !26, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [z] [line 12]
!29 = metadata !{i32 786449, metadata !30, i32 1, metadata !"clang version 3.4.2 (tags/RELEASE_34/dot2-final)", i1 true, metadata !"", i32 0, metadata !2, metadata !2, metadata !31, metadata !2, metadata !2, metadata !""} ; [ DW_TAG_compile_unit ] [/home
!30 = metadata !{metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic/klee_int.c", metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic"}
!31 = metadata !{metadata !32}
!32 = metadata !{i32 786478, metadata !33, metadata !34, metadata !"klee_int", metadata !"klee_int", metadata !"", i32 13, metadata !35, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 true, i32 (i8*)* @klee_int, null, null, metadata !41, i32 13} ; [ 
!33 = metadata !{metadata !"klee_int.c", metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic"}
!34 = metadata !{i32 786473, metadata !33}        ; [ DW_TAG_file_type ] [/home/ivan/Workspaces/DrE/runtime/Intrinsic/klee_int.c]
!35 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !36, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!36 = metadata !{metadata !37, metadata !38}
!37 = metadata !{i32 786468, null, null, metadata !"int", i32 0, i64 32, i64 32, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ] [int] [line 0, size 32, align 32, offset 0, enc DW_ATE_signed]
!38 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, metadata !39} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from ]
!39 = metadata !{i32 786470, null, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, metadata !40} ; [ DW_TAG_const_type ] [line 0, size 0, align 0, offset 0] [from char]
!40 = metadata !{i32 786468, null, null, metadata !"char", i32 0, i64 8, i64 8, i64 0, i32 0, i32 6} ; [ DW_TAG_base_type ] [char] [line 0, size 8, align 8, offset 0, enc DW_ATE_signed_char]
!41 = metadata !{metadata !42, metadata !43}
!42 = metadata !{i32 786689, metadata !32, metadata !"name", metadata !34, i32 16777229, metadata !38, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [name] [line 13]
!43 = metadata !{i32 786688, metadata !32, metadata !"x", metadata !34, i32 14, metadata !37, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [x] [line 14]
!44 = metadata !{i32 786449, metadata !45, i32 1, metadata !"clang version 3.4.2 (tags/RELEASE_34/dot2-final)", i1 true, metadata !"", i32 0, metadata !2, metadata !2, metadata !46, metadata !2, metadata !2, metadata !""} ; [ DW_TAG_compile_unit ] [/home
!45 = metadata !{metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic/klee_overshift_check.c", metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic"}
!46 = metadata !{metadata !47}
!47 = metadata !{i32 786478, metadata !48, metadata !49, metadata !"klee_overshift_check", metadata !"klee_overshift_check", metadata !"", i32 20, metadata !50, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 true, void (i64, i64)* @klee_overshift_che
!48 = metadata !{metadata !"klee_overshift_check.c", metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic"}
!49 = metadata !{i32 786473, metadata !48}        ; [ DW_TAG_file_type ] [/home/ivan/Workspaces/DrE/runtime/Intrinsic/klee_overshift_check.c]
!50 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !51, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!51 = metadata !{null, metadata !52, metadata !52}
!52 = metadata !{i32 786468, null, null, metadata !"long long unsigned int", i32 0, i64 64, i64 64, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [long long unsigned int] [line 0, size 64, align 64, offset 0, enc DW_ATE_unsigned]
!53 = metadata !{metadata !54, metadata !55}
!54 = metadata !{i32 786689, metadata !47, metadata !"bitWidth", metadata !49, i32 16777236, metadata !52, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [bitWidth] [line 20]
!55 = metadata !{i32 786689, metadata !47, metadata !"shift", metadata !49, i32 33554452, metadata !52, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [shift] [line 20]
!56 = metadata !{i32 786449, metadata !57, i32 1, metadata !"clang version 3.4.2 (tags/RELEASE_34/dot2-final)", i1 true, metadata !"", i32 0, metadata !2, metadata !2, metadata !58, metadata !2, metadata !2, metadata !""} ; [ DW_TAG_compile_unit ] [/home
!57 = metadata !{metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic/klee_range.c", metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic"}
!58 = metadata !{metadata !59}
!59 = metadata !{i32 786478, metadata !60, metadata !61, metadata !"klee_range", metadata !"klee_range", metadata !"", i32 13, metadata !62, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 true, i32 (i32, i32, i8*)* @klee_range, null, null, metadata !
!60 = metadata !{metadata !"klee_range.c", metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic"}
!61 = metadata !{i32 786473, metadata !60}        ; [ DW_TAG_file_type ] [/home/ivan/Workspaces/DrE/runtime/Intrinsic/klee_range.c]
!62 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !63, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!63 = metadata !{metadata !37, metadata !37, metadata !37, metadata !38}
!64 = metadata !{metadata !65, metadata !66, metadata !67, metadata !68}
!65 = metadata !{i32 786689, metadata !59, metadata !"start", metadata !61, i32 16777229, metadata !37, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [start] [line 13]
!66 = metadata !{i32 786689, metadata !59, metadata !"end", metadata !61, i32 33554445, metadata !37, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [end] [line 13]
!67 = metadata !{i32 786689, metadata !59, metadata !"name", metadata !61, i32 50331661, metadata !38, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [name] [line 13]
!68 = metadata !{i32 786688, metadata !59, metadata !"x", metadata !61, i32 14, metadata !37, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [x] [line 14]
!69 = metadata !{i32 786449, metadata !70, i32 1, metadata !"clang version 3.4.2 (tags/RELEASE_34/dot2-final)", i1 true, metadata !"", i32 0, metadata !2, metadata !2, metadata !71, metadata !2, metadata !2, metadata !""} ; [ DW_TAG_compile_unit ] [/home
!70 = metadata !{metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic/memcpy.c", metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic"}
!71 = metadata !{metadata !72}
!72 = metadata !{i32 786478, metadata !73, metadata !74, metadata !"memcpy", metadata !"memcpy", metadata !"", i32 12, metadata !75, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 true, i8* (i8*, i8*, i64)* @memcpy, null, null, metadata !82, i32 12} 
!73 = metadata !{metadata !"memcpy.c", metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic"}
!74 = metadata !{i32 786473, metadata !73}        ; [ DW_TAG_file_type ] [/home/ivan/Workspaces/DrE/runtime/Intrinsic/memcpy.c]
!75 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !76, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!76 = metadata !{metadata !77, metadata !77, metadata !78, metadata !80}
!77 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, null} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from ]
!78 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, metadata !79} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from ]
!79 = metadata !{i32 786470, null, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null} ; [ DW_TAG_const_type ] [line 0, size 0, align 0, offset 0] [from ]
!80 = metadata !{i32 786454, metadata !73, null, metadata !"size_t", i32 42, i64 0, i64 0, i64 0, i32 0, metadata !81} ; [ DW_TAG_typedef ] [size_t] [line 42, size 0, align 0, offset 0] [from long unsigned int]
!81 = metadata !{i32 786468, null, null, metadata !"long unsigned int", i32 0, i64 64, i64 64, i64 0, i32 0, i32 7} ; [ DW_TAG_base_type ] [long unsigned int] [line 0, size 64, align 64, offset 0, enc DW_ATE_unsigned]
!82 = metadata !{metadata !83, metadata !84, metadata !85, metadata !86, metadata !88}
!83 = metadata !{i32 786689, metadata !72, metadata !"destaddr", metadata !74, i32 16777228, metadata !77, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [destaddr] [line 12]
!84 = metadata !{i32 786689, metadata !72, metadata !"srcaddr", metadata !74, i32 33554444, metadata !78, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [srcaddr] [line 12]
!85 = metadata !{i32 786689, metadata !72, metadata !"len", metadata !74, i32 50331660, metadata !80, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [len] [line 12]
!86 = metadata !{i32 786688, metadata !72, metadata !"dest", metadata !74, i32 13, metadata !87, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [dest] [line 13]
!87 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, metadata !40} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from char]
!88 = metadata !{i32 786688, metadata !72, metadata !"src", metadata !74, i32 14, metadata !38, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [src] [line 14]
!89 = metadata !{i32 786449, metadata !90, i32 1, metadata !"clang version 3.4.2 (tags/RELEASE_34/dot2-final)", i1 true, metadata !"", i32 0, metadata !2, metadata !2, metadata !91, metadata !2, metadata !2, metadata !""} ; [ DW_TAG_compile_unit ] [/home
!90 = metadata !{metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic/memmove.c", metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic"}
!91 = metadata !{metadata !92}
!92 = metadata !{i32 786478, metadata !93, metadata !94, metadata !"memmove", metadata !"memmove", metadata !"", i32 12, metadata !95, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 true, i8* (i8*, i8*, i64)* @memmove, null, null, metadata !98, i32 1
!93 = metadata !{metadata !"memmove.c", metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic"}
!94 = metadata !{i32 786473, metadata !93}        ; [ DW_TAG_file_type ] [/home/ivan/Workspaces/DrE/runtime/Intrinsic/memmove.c]
!95 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !96, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!96 = metadata !{metadata !77, metadata !77, metadata !78, metadata !97}
!97 = metadata !{i32 786454, metadata !93, null, metadata !"size_t", i32 42, i64 0, i64 0, i64 0, i32 0, metadata !81} ; [ DW_TAG_typedef ] [size_t] [line 42, size 0, align 0, offset 0] [from long unsigned int]
!98 = metadata !{metadata !99, metadata !100, metadata !101, metadata !102, metadata !103}
!99 = metadata !{i32 786689, metadata !92, metadata !"dst", metadata !94, i32 16777228, metadata !77, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [dst] [line 12]
!100 = metadata !{i32 786689, metadata !92, metadata !"src", metadata !94, i32 33554444, metadata !78, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [src] [line 12]
!101 = metadata !{i32 786689, metadata !92, metadata !"count", metadata !94, i32 50331660, metadata !97, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [count] [line 12]
!102 = metadata !{i32 786688, metadata !92, metadata !"a", metadata !94, i32 13, metadata !87, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [a] [line 13]
!103 = metadata !{i32 786688, metadata !92, metadata !"b", metadata !94, i32 14, metadata !38, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [b] [line 14]
!104 = metadata !{i32 786449, metadata !105, i32 1, metadata !"clang version 3.4.2 (tags/RELEASE_34/dot2-final)", i1 true, metadata !"", i32 0, metadata !2, metadata !2, metadata !106, metadata !2, metadata !2, metadata !""} ; [ DW_TAG_compile_unit ] [/h
!105 = metadata !{metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic/mempcpy.c", metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic"}
!106 = metadata !{metadata !107}
!107 = metadata !{i32 786478, metadata !108, metadata !109, metadata !"mempcpy", metadata !"mempcpy", metadata !"", i32 11, metadata !110, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 true, i8* (i8*, i8*, i64)* @mempcpy, null, null, metadata !113, 
!108 = metadata !{metadata !"mempcpy.c", metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic"}
!109 = metadata !{i32 786473, metadata !108}      ; [ DW_TAG_file_type ] [/home/ivan/Workspaces/DrE/runtime/Intrinsic/mempcpy.c]
!110 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !111, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!111 = metadata !{metadata !77, metadata !77, metadata !78, metadata !112}
!112 = metadata !{i32 786454, metadata !108, null, metadata !"size_t", i32 42, i64 0, i64 0, i64 0, i32 0, metadata !81} ; [ DW_TAG_typedef ] [size_t] [line 42, size 0, align 0, offset 0] [from long unsigned int]
!113 = metadata !{metadata !114, metadata !115, metadata !116, metadata !117, metadata !118}
!114 = metadata !{i32 786689, metadata !107, metadata !"destaddr", metadata !109, i32 16777227, metadata !77, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [destaddr] [line 11]
!115 = metadata !{i32 786689, metadata !107, metadata !"srcaddr", metadata !109, i32 33554443, metadata !78, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [srcaddr] [line 11]
!116 = metadata !{i32 786689, metadata !107, metadata !"len", metadata !109, i32 50331659, metadata !112, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [len] [line 11]
!117 = metadata !{i32 786688, metadata !107, metadata !"dest", metadata !109, i32 12, metadata !87, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [dest] [line 12]
!118 = metadata !{i32 786688, metadata !107, metadata !"src", metadata !109, i32 13, metadata !38, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [src] [line 13]
!119 = metadata !{i32 786449, metadata !120, i32 1, metadata !"clang version 3.4.2 (tags/RELEASE_34/dot2-final)", i1 true, metadata !"", i32 0, metadata !2, metadata !2, metadata !121, metadata !2, metadata !2, metadata !""} ; [ DW_TAG_compile_unit ] [/h
!120 = metadata !{metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic/memset.c", metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic"}
!121 = metadata !{metadata !122}
!122 = metadata !{i32 786478, metadata !123, metadata !124, metadata !"memset", metadata !"memset", metadata !"", i32 11, metadata !125, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 true, i8* (i8*, i32, i64)* @memset, null, null, metadata !128, i32
!123 = metadata !{metadata !"memset.c", metadata !"/home/ivan/Workspaces/DrE/runtime/Intrinsic"}
!124 = metadata !{i32 786473, metadata !123}      ; [ DW_TAG_file_type ] [/home/ivan/Workspaces/DrE/runtime/Intrinsic/memset.c]
!125 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !126, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!126 = metadata !{metadata !77, metadata !77, metadata !37, metadata !127}
!127 = metadata !{i32 786454, metadata !123, null, metadata !"size_t", i32 42, i64 0, i64 0, i64 0, i32 0, metadata !81} ; [ DW_TAG_typedef ] [size_t] [line 42, size 0, align 0, offset 0] [from long unsigned int]
!128 = metadata !{metadata !129, metadata !130, metadata !131, metadata !132}
!129 = metadata !{i32 786689, metadata !122, metadata !"dst", metadata !124, i32 16777227, metadata !77, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [dst] [line 11]
!130 = metadata !{i32 786689, metadata !122, metadata !"s", metadata !124, i32 33554443, metadata !37, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [s] [line 11]
!131 = metadata !{i32 786689, metadata !122, metadata !"count", metadata !124, i32 50331659, metadata !127, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [count] [line 11]
!132 = metadata !{i32 786688, metadata !122, metadata !"a", metadata !124, i32 12, metadata !133, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [a] [line 12]
!133 = metadata !{i32 786447, null, null, metadata !"", i32 0, i64 64, i64 64, i64 0, i32 0, metadata !134} ; [ DW_TAG_pointer_type ] [line 0, size 64, align 64, offset 0] [from ]
!134 = metadata !{i32 786485, null, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, metadata !40} ; [ DW_TAG_volatile_type ] [line 0, size 0, align 0, offset 0] [from char]
!135 = metadata !{i32 2, metadata !"Dwarf Version", i32 4}
!136 = metadata !{i32 1, metadata !"Debug Info Version", i32 1}
!137 = metadata !{metadata !"clang version 3.4.2 (tags/RELEASE_34/dot2-final)"}
!138 = metadata !{i32 8, i32 0, metadata !4, null} ; [ DW_TAG_imported_declaration ]
!139 = metadata !{i32 9, i32 0, metadata !4, null}
!140 = metadata !{i32 10, i32 0, metadata !4, null}
!141 = metadata !{i32 13, i32 0, metadata !142, null}
!142 = metadata !{i32 786443, metadata !1, metadata !4, i32 11, i32 0, i32 0} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/examples2/fig4-mod2/main.c]
!143 = metadata !{i32 14, i32 0, metadata !142, null}
!144 = metadata !{i32 15, i32 0, metadata !142, null}
!145 = metadata !{i32 16, i32 0, metadata !146, null}
!146 = metadata !{i32 786443, metadata !1, metadata !4, i32 16, i32 0, i32 1} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/examples2/fig4-mod2/main.c]
!147 = metadata !{i32 17, i32 0, metadata !146, null}
!148 = metadata !{i32 18, i32 0, metadata !149, null}
!149 = metadata !{i32 786443, metadata !1, metadata !146, i32 18, i32 0, i32 2} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/examples2/fig4-mod2/main.c]
!150 = metadata !{i32 19, i32 0, metadata !149, null}
!151 = metadata !{i32 21, i32 0, metadata !149, null}
!152 = metadata !{i32 22, i32 0, metadata !4, null}
!153 = metadata !{i32 31, i32 0, metadata !9, null}
!154 = metadata !{i32 32, i32 0, metadata !9, null}
!155 = metadata !{i32 33, i32 0, metadata !9, null}
!156 = metadata !{i32 34, i32 0, metadata !9, null}
!157 = metadata !{i32 36, i32 0, metadata !9, null}
!158 = metadata !{i32 37, i32 0, metadata !9, null}
!159 = metadata !{i32 39, i32 0, metadata !160, null}
!160 = metadata !{i32 786443, metadata !1, metadata !9, i32 38, i32 0, i32 3} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/examples2/fig4-mod2/main.c]
!161 = metadata !{i32 40, i32 0, metadata !160, null}
!162 = metadata !{i32 41, i32 0, metadata !163, null}
!163 = metadata !{i32 786443, metadata !1, metadata !160, i32 41, i32 0, i32 4} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/examples2/fig4-mod2/main.c]
!164 = metadata !{i32 42, i32 0, metadata !165, null}
!165 = metadata !{i32 786443, metadata !1, metadata !160, i32 42, i32 0, i32 5} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/examples2/fig4-mod2/main.c]
!166 = metadata !{i32 47, i32 0, metadata !9, null}
!167 = metadata !{i32 48, i32 0, metadata !9, null}
!168 = metadata !{i32 61, i32 0, metadata !12, null}
!169 = metadata !{i32 63, i32 0, metadata !12, null}
!170 = metadata !{i32 64, i32 0, metadata !12, null}
!171 = metadata !{i32 65, i32 0, metadata !12, null}
!172 = metadata !{i32 13, i32 0, metadata !173, null}
!173 = metadata !{i32 786443, metadata !22, metadata !21, i32 13, i32 0, i32 0} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/runtime/Intrinsic/klee_div_zero_check.c]
!174 = metadata !{i32 14, i32 0, metadata !173, null}
!175 = metadata !{i32 15, i32 0, metadata !21, null}
!176 = metadata !{i32 15, i32 0, metadata !32, null}
!177 = metadata !{i32 16, i32 0, metadata !32, null}
!178 = metadata !{metadata !179, metadata !179, i64 0}
!179 = metadata !{metadata !"int", metadata !180, i64 0}
!180 = metadata !{metadata !"omnipotent char", metadata !181, i64 0}
!181 = metadata !{metadata !"Simple C/C++ TBAA"}
!182 = metadata !{i32 21, i32 0, metadata !183, null}
!183 = metadata !{i32 786443, metadata !48, metadata !47, i32 21, i32 0, i32 0} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/runtime/Intrinsic/klee_overshift_check.c]
!184 = metadata !{i32 27, i32 0, metadata !185, null}
!185 = metadata !{i32 786443, metadata !48, metadata !183, i32 21, i32 0, i32 1} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/runtime/Intrinsic/klee_overshift_check.c]
!186 = metadata !{i32 29, i32 0, metadata !47, null}
!187 = metadata !{i32 16, i32 0, metadata !188, null}
!188 = metadata !{i32 786443, metadata !60, metadata !59, i32 16, i32 0, i32 0} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/runtime/Intrinsic/klee_range.c]
!189 = metadata !{i32 17, i32 0, metadata !188, null}
!190 = metadata !{i32 19, i32 0, metadata !191, null}
!191 = metadata !{i32 786443, metadata !60, metadata !59, i32 19, i32 0, i32 1} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/runtime/Intrinsic/klee_range.c]
!192 = metadata !{i32 22, i32 0, metadata !193, null}
!193 = metadata !{i32 786443, metadata !60, metadata !191, i32 21, i32 0, i32 3} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/runtime/Intrinsic/klee_range.c]
!194 = metadata !{i32 25, i32 0, metadata !195, null}
!195 = metadata !{i32 786443, metadata !60, metadata !193, i32 25, i32 0, i32 4} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/runtime/Intrinsic/klee_range.c]
!196 = metadata !{i32 26, i32 0, metadata !197, null}
!197 = metadata !{i32 786443, metadata !60, metadata !195, i32 25, i32 0, i32 5} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/runtime/Intrinsic/klee_range.c]
!198 = metadata !{i32 27, i32 0, metadata !197, null}
!199 = metadata !{i32 28, i32 0, metadata !200, null}
!200 = metadata !{i32 786443, metadata !60, metadata !195, i32 27, i32 0, i32 6} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/runtime/Intrinsic/klee_range.c]
!201 = metadata !{i32 29, i32 0, metadata !200, null}
!202 = metadata !{i32 32, i32 0, metadata !193, null}
!203 = metadata !{i32 34, i32 0, metadata !59, null}
!204 = metadata !{i32 16, i32 0, metadata !72, null}
!205 = metadata !{i32 17, i32 0, metadata !72, null}
!206 = metadata !{metadata !206, metadata !207, metadata !208}
!207 = metadata !{metadata !"llvm.vectorizer.width", i32 1}
!208 = metadata !{metadata !"llvm.vectorizer.unroll", i32 1}
!209 = metadata !{metadata !180, metadata !180, i64 0}
!210 = metadata !{metadata !210, metadata !207, metadata !208}
!211 = metadata !{i32 18, i32 0, metadata !72, null}
!212 = metadata !{i32 16, i32 0, metadata !213, null}
!213 = metadata !{i32 786443, metadata !93, metadata !92, i32 16, i32 0, i32 0} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/runtime/Intrinsic/memmove.c]
!214 = metadata !{i32 19, i32 0, metadata !215, null}
!215 = metadata !{i32 786443, metadata !93, metadata !92, i32 19, i32 0, i32 1} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/runtime/Intrinsic/memmove.c]
!216 = metadata !{i32 20, i32 0, metadata !217, null}
!217 = metadata !{i32 786443, metadata !93, metadata !215, i32 19, i32 0, i32 2} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/runtime/Intrinsic/memmove.c]
!218 = metadata !{metadata !218, metadata !207, metadata !208}
!219 = metadata !{metadata !219, metadata !207, metadata !208}
!220 = metadata !{i32 22, i32 0, metadata !221, null}
!221 = metadata !{i32 786443, metadata !93, metadata !215, i32 21, i32 0, i32 3} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/runtime/Intrinsic/memmove.c]
!222 = metadata !{i32 24, i32 0, metadata !221, null}
!223 = metadata !{i32 23, i32 0, metadata !221, null}
!224 = metadata !{metadata !224, metadata !207, metadata !208}
!225 = metadata !{metadata !225, metadata !207, metadata !208}
!226 = metadata !{i32 28, i32 0, metadata !92, null}
!227 = metadata !{i32 15, i32 0, metadata !107, null}
!228 = metadata !{i32 16, i32 0, metadata !107, null}
!229 = metadata !{metadata !229, metadata !207, metadata !208}
!230 = metadata !{metadata !230, metadata !207, metadata !208}
!231 = metadata !{i32 17, i32 0, metadata !107, null}
!232 = metadata !{i32 13, i32 0, metadata !122, null}
!233 = metadata !{i32 14, i32 0, metadata !122, null}
!234 = metadata !{i32 15, i32 0, metadata !122, null}
