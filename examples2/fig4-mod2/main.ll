; ModuleID = 'main.c'
target datalayout = "e-p:16:16:16-i8:8:8-i16:16:16-i32:16:32-n8:16"
target triple = "msp430"

@adc = global i16 0, align 2
@.str = private unnamed_addr constant [5 x i8] c"mode\00", align 1
@num_of_adc_reads = global i16 0, align 2
@llvm.used = appending global [1 x i8*] [i8* bitcast (void ()* @ADC10_ISR to i8*)], section "llvm.metadata"

@__isr_5 = alias void ()* @ADC10_ISR

; Function Attrs: nounwind
define i16 @get_acceleration(i16 %mode) #0 {
entry:
  %retval = alloca i16, align 2
  %mode.addr = alloca i16, align 2
  %i = alloca i16, align 2
  store i16 %mode, i16* %mode.addr, align 2
  call void @llvm.dbg.declare(metadata !{i16* %mode.addr}, metadata !21), !dbg !22
  call void @llvm.dbg.declare(metadata !{i16* %i}, metadata !23), !dbg !24
  store i16 0, i16* %i, align 2, !dbg !24
  %call = call i16 bitcast (i16 (...)* @__bis_SR_register to i16 (i16)*)(i16 24), !dbg !25
  br label %while.cond, !dbg !26

while.cond:                                       ; preds = %while.body, %entry
  %0 = load i16* @adc, align 2, !dbg !26
  %cmp = icmp sge i16 %0, 15, !dbg !26
  br i1 %cmp, label %while.body, label %while.end, !dbg !26

while.body:                                       ; preds = %while.cond
  %1 = load i16* %i, align 2, !dbg !27
  %inc = add nsw i16 %1, 1, !dbg !27
  store i16 %inc, i16* %i, align 2, !dbg !27
  %call1 = call i16 bitcast (i16 (...)* @__bis_SR_register to i16 (i16)*)(i16 24), !dbg !29
  br label %while.cond, !dbg !30

while.end:                                        ; preds = %while.cond
  %2 = load i16* %i, align 2, !dbg !31
  %cmp2 = icmp sgt i16 %2, 15, !dbg !31
  br i1 %cmp2, label %land.lhs.true, label %if.else, !dbg !31

land.lhs.true:                                    ; preds = %while.end
  %3 = load i16* %mode.addr, align 2, !dbg !31
  %cmp3 = icmp eq i16 %3, 97, !dbg !31
  br i1 %cmp3, label %if.then, label %if.else, !dbg !31

if.then:                                          ; preds = %land.lhs.true
  store i16 1, i16* %retval, !dbg !33
  br label %return, !dbg !33

if.else:                                          ; preds = %land.lhs.true, %while.end
  %4 = load i16* %mode.addr, align 2, !dbg !34
  %cmp4 = icmp eq i16 %4, 97, !dbg !34
  br i1 %cmp4, label %if.then5, label %if.else6, !dbg !34

if.then5:                                         ; preds = %if.else
  store i16 2, i16* %retval, !dbg !36
  br label %return, !dbg !36

if.else6:                                         ; preds = %if.else
  store i16 3, i16* %retval, !dbg !37
  br label %return, !dbg !37

return:                                           ; preds = %if.else6, %if.then5, %if.then
  %5 = load i16* %retval, !dbg !38
  ret i16 %5, !dbg !38
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
  call void @llvm.dbg.declare(metadata !{i16* %val}, metadata !39), !dbg !40
  store i16 0, i16* %val, align 2, !dbg !40
  call void @llvm.dbg.declare(metadata !{i16* %val_repv}, metadata !41), !dbg !40
  store i16 0, i16* %val_repv, align 2, !dbg !40
  call void @llvm.dbg.declare(metadata !{i16* %tick}, metadata !42), !dbg !43
  store i16 0, i16* %tick, align 2, !dbg !43
  call void @llvm.dbg.declare(metadata !{[3 x i16]* %acceleration}, metadata !44), !dbg !48
  %0 = bitcast [3 x i16]* %acceleration to i8*, !dbg !48
  call void @llvm.memset.p0i8.i16(i8* %0, i8 0, i16 6, i32 2, i1 false), !dbg !48
  call void @llvm.dbg.declare(metadata !{i16* %j}, metadata !49), !dbg !50
  store i16 0, i16* %j, align 2, !dbg !50
  call void @llvm.dbg.declare(metadata !{i16* %mode}, metadata !51), !dbg !52
  %call = call i16 bitcast (i16 (...)* @klee_make_symbolic to i16 (i16*, i16, i8*)*)(i16* %mode, i16 2, i8* getelementptr inbounds ([5 x i8]* @.str, i32 0, i32 0)), !dbg !53
  br label %while.body, !dbg !54

while.body:                                       ; preds = %entry, %if.end10
  %1 = load i16* %mode, align 2, !dbg !55
  %call1 = call i16 @get_acceleration(i16 %1), !dbg !55
  %2 = load i16* %j, align 2, !dbg !55
  %arrayidx = getelementptr inbounds [3 x i16]* %acceleration, i32 0, i16 %2, !dbg !55
  store i16 %call1, i16* %arrayidx, align 2, !dbg !55
  %3 = load i16* %j, align 2, !dbg !57
  %inc = add nsw i16 %3, 1, !dbg !57
  store i16 %inc, i16* %j, align 2, !dbg !57
  %4 = load i16* %j, align 2, !dbg !58
  %cmp = icmp eq i16 %4, 3, !dbg !58
  br i1 %cmp, label %if.then, label %if.end, !dbg !58

if.then:                                          ; preds = %while.body
  store i16 0, i16* %j, align 2, !dbg !58
  br label %if.end, !dbg !58

if.end:                                           ; preds = %if.then, %while.body
  %arrayidx2 = getelementptr inbounds [3 x i16]* %acceleration, i32 0, i16 0, !dbg !60
  %5 = load i16* %arrayidx2, align 2, !dbg !60
  %cmp3 = icmp eq i16 %5, 1, !dbg !60
  br i1 %cmp3, label %land.lhs.true, label %if.end10, !dbg !60

land.lhs.true:                                    ; preds = %if.end
  %arrayidx4 = getelementptr inbounds [3 x i16]* %acceleration, i32 0, i16 1, !dbg !60
  %6 = load i16* %arrayidx4, align 2, !dbg !60
  %cmp5 = icmp eq i16 %6, 1, !dbg !60
  br i1 %cmp5, label %land.lhs.true6, label %if.end10, !dbg !60

land.lhs.true6:                                   ; preds = %land.lhs.true
  %arrayidx7 = getelementptr inbounds [3 x i16]* %acceleration, i32 0, i16 2, !dbg !60
  %7 = load i16* %arrayidx7, align 2, !dbg !60
  %cmp8 = icmp eq i16 %7, 1, !dbg !60
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !60

if.then9:                                         ; preds = %land.lhs.true6
  br label %while.end, !dbg !62

if.end10:                                         ; preds = %land.lhs.true6, %land.lhs.true, %if.end
  br label %while.body, !dbg !63

while.end:                                        ; preds = %if.then9
  %call11 = call i16 @assert(i16 0), !dbg !64
  ret i16 0, !dbg !65
}

; Function Attrs: nounwind
declare void @llvm.memset.p0i8.i16(i8* nocapture, i8, i16, i32, i1) #3

declare i16 @klee_make_symbolic(...) #2

declare i16 @assert(i16) #2

; Function Attrs: noinline nounwind
define msp430_intrcc void @ADC10_ISR() #4 {
entry:
  %0 = load volatile i16* inttoptr (i16 436 to i16*), align 2, !dbg !66
  store i16 %0, i16* @adc, align 2, !dbg !66
  %1 = load i16* @num_of_adc_reads, align 2, !dbg !67
  %inc = add nsw i16 %1, 1, !dbg !67
  store i16 %inc, i16* @num_of_adc_reads, align 2, !dbg !67
  %call = call i16 bitcast (i16 (...)* @__bic_SR_register_on_exit to i16 (i16)*)(i16 16), !dbg !68
  ret void, !dbg !69
}

declare i16 @__bic_SR_register_on_exit(...) #2

attributes #0 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }
attributes #4 = { noinline nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!18, !19}
!llvm.ident = !{!20}

!0 = metadata !{i32 786449, metadata !1, i32 12, metadata !"clang version 3.4.2 (tags/RELEASE_34/dot2-final)", i1 false, metadata !"", i32 0, metadata !2, metadata !2, metadata !3, metadata !15, metadata !2, metadata !""} ; [ DW_TAG_compile_unit ] [/home/ivan/Workspaces/DrE/examples2/fig4-mod2/main.c] [DW_LANG_C99]
!1 = metadata !{metadata !"main.c", metadata !"/home/ivan/Workspaces/DrE/examples2/fig4-mod2"}
!2 = metadata !{i32 0}
!3 = metadata !{metadata !4, metadata !9, metadata !12}
!4 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"get_acceleration", metadata !"get_acceleration", metadata !"", i32 6, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 false, i16 (i16)* @get_acceleration, null, null, metadata !2, i32 7} ; [ DW_TAG_subprogram ] [line 6] [def] [scope 7] [get_acceleration]
!5 = metadata !{i32 786473, metadata !1}          ; [ DW_TAG_file_type ] [/home/ivan/Workspaces/DrE/examples2/fig4-mod2/main.c]
!6 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !7, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!7 = metadata !{metadata !8, metadata !8}
!8 = metadata !{i32 786468, null, null, metadata !"int", i32 0, i64 16, i64 16, i64 0, i32 0, i32 5} ; [ DW_TAG_base_type ] [int] [line 0, size 16, align 16, offset 0, enc DW_ATE_signed]
!9 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"main", metadata !"main", metadata !"", i32 29, metadata !10, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, i16 ()* @main, null, null, metadata !2, i32 30} ; [ DW_TAG_subprogram ] [line 29] [def] [scope 30] [main]
!10 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !11, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!11 = metadata !{metadata !8}
!12 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"ADC10_ISR", metadata !"ADC10_ISR", metadata !"", i32 56, metadata !13, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 false, void ()* @ADC10_ISR, null, null, metadata !2, i32 60} ; [ DW_TAG_subprogram ] [line 56] [def] [scope 60] [ADC10_ISR]
!13 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !14, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!14 = metadata !{null}
!15 = metadata !{metadata !16, metadata !17}
!16 = metadata !{i32 786484, i32 0, null, metadata !"adc", metadata !"adc", metadata !"", metadata !5, i32 4, metadata !8, i32 0, i32 1, i16* @adc, null} ; [ DW_TAG_variable ] [adc] [line 4] [def]
!17 = metadata !{i32 786484, i32 0, null, metadata !"num_of_adc_reads", metadata !"num_of_adc_reads", metadata !"", metadata !5, i32 51, metadata !8, i32 0, i32 1, i16* @num_of_adc_reads, null} ; [ DW_TAG_variable ] [num_of_adc_reads] [line 51] [def]
!18 = metadata !{i32 2, metadata !"Dwarf Version", i32 4}
!19 = metadata !{i32 1, metadata !"Debug Info Version", i32 1}
!20 = metadata !{metadata !"clang version 3.4.2 (tags/RELEASE_34/dot2-final)"}
!21 = metadata !{i32 786689, metadata !4, metadata !"mode", metadata !5, i32 16777222, metadata !8, i32 0, i32 0} ; [ DW_TAG_arg_variable ] [mode] [line 6]
!22 = metadata !{i32 6, i32 0, metadata !4, null}
!23 = metadata !{i32 786688, metadata !4, metadata !"i", metadata !5, i32 8, metadata !8, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [i] [line 8]
!24 = metadata !{i32 8, i32 0, metadata !4, null} ; [ DW_TAG_imported_declaration ]
!25 = metadata !{i32 9, i32 0, metadata !4, null}
!26 = metadata !{i32 10, i32 0, metadata !4, null}
!27 = metadata !{i32 13, i32 0, metadata !28, null}
!28 = metadata !{i32 786443, metadata !1, metadata !4, i32 11, i32 0, i32 0} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/examples2/fig4-mod2/main.c]
!29 = metadata !{i32 14, i32 0, metadata !28, null}
!30 = metadata !{i32 15, i32 0, metadata !28, null}
!31 = metadata !{i32 16, i32 0, metadata !32, null}
!32 = metadata !{i32 786443, metadata !1, metadata !4, i32 16, i32 0, i32 1} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/examples2/fig4-mod2/main.c]
!33 = metadata !{i32 17, i32 0, metadata !32, null}
!34 = metadata !{i32 18, i32 0, metadata !35, null}
!35 = metadata !{i32 786443, metadata !1, metadata !32, i32 18, i32 0, i32 2} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/examples2/fig4-mod2/main.c]
!36 = metadata !{i32 19, i32 0, metadata !35, null}
!37 = metadata !{i32 21, i32 0, metadata !35, null}
!38 = metadata !{i32 22, i32 0, metadata !4, null}
!39 = metadata !{i32 786688, metadata !9, metadata !"val", metadata !5, i32 31, metadata !8, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [val] [line 31]
!40 = metadata !{i32 31, i32 0, metadata !9, null}
!41 = metadata !{i32 786688, metadata !9, metadata !"val_repv", metadata !5, i32 31, metadata !8, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [val_repv] [line 31]
!42 = metadata !{i32 786688, metadata !9, metadata !"tick", metadata !5, i32 32, metadata !8, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [tick] [line 32]
!43 = metadata !{i32 32, i32 0, metadata !9, null}
!44 = metadata !{i32 786688, metadata !9, metadata !"acceleration", metadata !5, i32 33, metadata !45, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [acceleration] [line 33]
!45 = metadata !{i32 786433, null, null, metadata !"", i32 0, i64 48, i64 16, i32 0, i32 0, metadata !8, metadata !46, i32 0, null, null, null} ; [ DW_TAG_array_type ] [line 0, size 48, align 16, offset 0] [from int]
!46 = metadata !{metadata !47}
!47 = metadata !{i32 786465, i64 0, i64 3}        ; [ DW_TAG_subrange_type ] [0, 2]
!48 = metadata !{i32 33, i32 0, metadata !9, null}
!49 = metadata !{i32 786688, metadata !9, metadata !"j", metadata !5, i32 34, metadata !8, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [j] [line 34]
!50 = metadata !{i32 34, i32 0, metadata !9, null}
!51 = metadata !{i32 786688, metadata !9, metadata !"mode", metadata !5, i32 35, metadata !8, i32 0, i32 0} ; [ DW_TAG_auto_variable ] [mode] [line 35]
!52 = metadata !{i32 35, i32 0, metadata !9, null}
!53 = metadata !{i32 36, i32 0, metadata !9, null}
!54 = metadata !{i32 37, i32 0, metadata !9, null}
!55 = metadata !{i32 39, i32 0, metadata !56, null}
!56 = metadata !{i32 786443, metadata !1, metadata !9, i32 38, i32 0, i32 3} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/examples2/fig4-mod2/main.c]
!57 = metadata !{i32 40, i32 0, metadata !56, null}
!58 = metadata !{i32 41, i32 0, metadata !59, null}
!59 = metadata !{i32 786443, metadata !1, metadata !56, i32 41, i32 0, i32 4} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/examples2/fig4-mod2/main.c]
!60 = metadata !{i32 42, i32 0, metadata !61, null}
!61 = metadata !{i32 786443, metadata !1, metadata !56, i32 42, i32 0, i32 5} ; [ DW_TAG_lexical_block ] [/home/ivan/Workspaces/DrE/examples2/fig4-mod2/main.c]
!62 = metadata !{i32 45, i32 0, metadata !61, null}
!63 = metadata !{i32 46, i32 0, metadata !56, null}
!64 = metadata !{i32 47, i32 0, metadata !9, null}
!65 = metadata !{i32 48, i32 0, metadata !9, null}
!66 = metadata !{i32 61, i32 0, metadata !12, null}
!67 = metadata !{i32 63, i32 0, metadata !12, null}
!68 = metadata !{i32 64, i32 0, metadata !12, null}
!69 = metadata !{i32 65, i32 0, metadata !12, null}
