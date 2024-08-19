
@global_str = private unnamed_addr constant [3 x i8] c", \00", align 1
@global_str.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.3 = private unnamed_addr constant [16 x i8] c"Initial array: \00", align 1
@global_str.4 = private unnamed_addr constant [15 x i8] c"Sorted array: \00", align 1

declare void @writeInteger(i32)

declare void @writeByte(i8)

declare void @writeChar(i8)

declare void @writeString(ptr)

declare i32 @readInteger()

declare i8 @readByte()

declare i8 @readChar()

declare void @readString(i32, ptr)

declare i32 @extend(i8)

declare i8 @shrink(i32)

declare i32 @strlen(ptr)

declare i32 @strcmp(ptr, ptr)

declare void @strcpy(ptr, ptr)

declare void @strcat(ptr, ptr)

define i32 @main() {
entry:
  call void @main.1()
  ret i32 0
}

define void @main.1() {
main_entry:
  %seed = alloca i32, align 4
  %x = alloca [16 x i32], align 4
  %y = alloca [10 x i8], align 1
  %i = alloca i32, align 4
  %int_const = alloca i32, align 4
  store i32 65, ptr %int_const, align 4
  %0 = load i32, ptr %int_const, align 4
  store i32 %0, ptr %seed, align 4
  %int_const1 = alloca i32, align 4
  store i32 0, ptr %int_const1, align 4
  %1 = load i32, ptr %int_const1, align 4
  store i32 %1, ptr %i, align 4
  br label %cond

cond:                                             ; preds = %loop, %main_entry
  %int_const2 = alloca i32, align 4
  store i32 16, ptr %int_const2, align 4
  %left_load = load i32, ptr %i, align 4
  %right_load = load i32, ptr %int_const2, align 4
  %lttmp = icmp slt i32 %left_load, %right_load
  %2 = zext i1 %lttmp to i32
  %while_cond = icmp ne i32 %2, 0
  br i1 %while_cond, label %loop, label %afterloop

loop:                                             ; preds = %cond
  %int_const3 = alloca i32, align 4
  store i32 137, ptr %int_const3, align 4
  %left_load4 = load i32, ptr %seed, align 4
  %right_load5 = load i32, ptr %int_const3, align 4
  %binop_tmp = alloca i32, align 4
  %multmp = mul i32 %left_load4, %right_load5
  store i32 %multmp, ptr %binop_tmp, align 4
  %int_const6 = alloca i32, align 4
  store i32 220, ptr %int_const6, align 4
  %left_load7 = load i32, ptr %binop_tmp, align 4
  %right_load8 = load i32, ptr %int_const6, align 4
  %binop_tmp9 = alloca i32, align 4
  %addtmp = add i32 %left_load7, %right_load8
  store i32 %addtmp, ptr %binop_tmp9, align 4
  %left_load10 = load i32, ptr %binop_tmp9, align 4
  %right_load11 = load i32, ptr %i, align 4
  %binop_tmp12 = alloca i32, align 4
  %addtmp13 = add i32 %left_load10, %right_load11
  store i32 %addtmp13, ptr %binop_tmp12, align 4
  %int_const14 = alloca i32, align 4
  store i32 101, ptr %int_const14, align 4
  %left_load15 = load i32, ptr %binop_tmp12, align 4
  %right_load16 = load i32, ptr %int_const14, align 4
  %binop_tmp17 = alloca i32, align 4
  %modtmp = srem i32 %left_load15, %right_load16
  store i32 %modtmp, ptr %binop_tmp17, align 4
  %3 = load i32, ptr %binop_tmp17, align 4
  store i32 %3, ptr %seed, align 4
  %4 = load i32, ptr %seed, align 4
  %load_index = load i32, ptr %i, align 4
  %elementptr = getelementptr [16 x i32], ptr %x, i32 0, i32 %load_index
  store i32 %4, ptr %elementptr, align 4
  %int_const18 = alloca i32, align 4
  store i32 1, ptr %int_const18, align 4
  %left_load19 = load i32, ptr %i, align 4
  %right_load20 = load i32, ptr %int_const18, align 4
  %binop_tmp21 = alloca i32, align 4
  %addtmp22 = add i32 %left_load19, %right_load20
  store i32 %addtmp22, ptr %binop_tmp21, align 4
  %5 = load i32, ptr %binop_tmp21, align 4
  store i32 %5, ptr %i, align 4
  br label %cond

afterloop:                                        ; preds = %cond
  %str_const_alloca = alloca [16 x i8], align 1
  call void @llvm.memcpy.p0.p0.i32(ptr align 1 %str_const_alloca, ptr align 1 @global_str.3, i32 16, i1 false)
  %int_const23 = alloca i32, align 4
  store i32 16, ptr %int_const23, align 4
  %writeArray_arg = load i32, ptr %int_const23, align 4
  call void @writeArray(ptr %str_const_alloca, i32 %writeArray_arg, ptr %x)
  %int_const24 = alloca i32, align 4
  store i32 16, ptr %int_const24, align 4
  %bsort_arg = load i32, ptr %int_const24, align 4
  call void @bsort(i32 %bsort_arg, ptr %x)
  %str_const_alloca25 = alloca [15 x i8], align 1
  call void @llvm.memcpy.p0.p0.i32(ptr align 1 %str_const_alloca25, ptr align 1 @global_str.4, i32 15, i1 false)
  %int_const26 = alloca i32, align 4
  store i32 16, ptr %int_const26, align 4
  %writeArray_arg27 = load i32, ptr %int_const26, align 4
  call void @writeArray(ptr %str_const_alloca25, i32 %writeArray_arg27, ptr %x)
  ret void
}

define void @bsort(i32 %n, ptr %x) {
bsort_entry:
  %n1 = alloca i32, align 4
  store i32 %n, ptr %n1, align 4
  %x2 = alloca ptr, align 8
  store ptr %x, ptr %x2, align 8
  %changed = alloca i8, align 1
  %i = alloca i32, align 4
  %char_const = alloca i8, align 1
  store i8 121, ptr %char_const, align 1
  %0 = load i8, ptr %char_const, align 1
  store i8 %0, ptr %changed, align 1
  br label %cond

cond:                                             ; preds = %afterloop, %bsort_entry
  %char_const3 = alloca i8, align 1
  store i8 121, ptr %char_const3, align 1
  %left_load = load i8, ptr %changed, align 1
  %right_load = load i8, ptr %char_const3, align 1
  %eqtmp = icmp eq i8 %left_load, %right_load
  %1 = zext i1 %eqtmp to i32
  %while_cond = icmp ne i32 %1, 0
  br i1 %while_cond, label %loop, label %afterloop39

loop:                                             ; preds = %cond
  %char_const4 = alloca i8, align 1
  store i8 110, ptr %char_const4, align 1
  %2 = load i8, ptr %char_const4, align 1
  store i8 %2, ptr %changed, align 1
  %int_const = alloca i32, align 4
  store i32 0, ptr %int_const, align 4
  %3 = load i32, ptr %int_const, align 4
  store i32 %3, ptr %i, align 4
  br label %cond5

cond5:                                            ; preds = %ifcont, %loop
  %int_const6 = alloca i32, align 4
  store i32 1, ptr %int_const6, align 4
  %left_load7 = load i32, ptr %n1, align 4
  %right_load8 = load i32, ptr %int_const6, align 4
  %binop_tmp = alloca i32, align 4
  %subtmp = sub i32 %left_load7, %right_load8
  store i32 %subtmp, ptr %binop_tmp, align 4
  %left_load9 = load i32, ptr %i, align 4
  %right_load10 = load i32, ptr %binop_tmp, align 4
  %lttmp = icmp slt i32 %left_load9, %right_load10
  %4 = zext i1 %lttmp to i32
  %while_cond11 = icmp ne i32 %4, 0
  br i1 %while_cond11, label %loop12, label %afterloop

loop12:                                           ; preds = %cond5
  %load_index = load i32, ptr %i, align 4
  %x_arrayptr = load ptr, ptr %x2, align 8
  %elementptr = getelementptr i32, ptr %x_arrayptr, i32 %load_index
  %int_const13 = alloca i32, align 4
  store i32 1, ptr %int_const13, align 4
  %left_load14 = load i32, ptr %i, align 4
  %right_load15 = load i32, ptr %int_const13, align 4
  %binop_tmp16 = alloca i32, align 4
  %addtmp = add i32 %left_load14, %right_load15
  store i32 %addtmp, ptr %binop_tmp16, align 4
  %load_index17 = load i32, ptr %binop_tmp16, align 4
  %x_arrayptr18 = load ptr, ptr %x2, align 8
  %elementptr19 = getelementptr i32, ptr %x_arrayptr18, i32 %load_index17
  %left_load20 = load i32, ptr %elementptr, align 4
  %right_load21 = load i32, ptr %elementptr19, align 4
  %gttmp = icmp sgt i32 %left_load20, %right_load21
  %5 = zext i1 %gttmp to i32
  %if_cond = icmp ne i32 %5, 0
  br i1 %if_cond, label %then, label %else

then:                                             ; preds = %loop12
  %load_index22 = load i32, ptr %i, align 4
  %x_arrayptr23 = load ptr, ptr %x2, align 8
  %elementptr24 = getelementptr i32, ptr %x_arrayptr23, i32 %load_index22
  %int_const25 = alloca i32, align 4
  store i32 1, ptr %int_const25, align 4
  %left_load26 = load i32, ptr %i, align 4
  %right_load27 = load i32, ptr %int_const25, align 4
  %binop_tmp28 = alloca i32, align 4
  %addtmp29 = add i32 %left_load26, %right_load27
  store i32 %addtmp29, ptr %binop_tmp28, align 4
  %load_index30 = load i32, ptr %binop_tmp28, align 4
  %x_arrayptr31 = load ptr, ptr %x2, align 8
  %elementptr32 = getelementptr i32, ptr %x_arrayptr31, i32 %load_index30
  call void @swap(ptr %elementptr24, ptr %elementptr32)
  %char_const33 = alloca i8, align 1
  store i8 121, ptr %char_const33, align 1
  %6 = load i8, ptr %char_const33, align 1
  store i8 %6, ptr %changed, align 1
  br label %ifcont

else:                                             ; preds = %loop12
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  %int_const34 = alloca i32, align 4
  store i32 1, ptr %int_const34, align 4
  %left_load35 = load i32, ptr %i, align 4
  %right_load36 = load i32, ptr %int_const34, align 4
  %binop_tmp37 = alloca i32, align 4
  %addtmp38 = add i32 %left_load35, %right_load36
  store i32 %addtmp38, ptr %binop_tmp37, align 4
  %7 = load i32, ptr %binop_tmp37, align 4
  store i32 %7, ptr %i, align 4
  br label %cond5

afterloop:                                        ; preds = %cond5
  br label %cond

afterloop39:                                      ; preds = %cond
  ret void
}

define void @swap(ptr %x, ptr %y) {
swap_entry:
  %x1 = alloca ptr, align 8
  store ptr %x, ptr %x1, align 8
  %y2 = alloca ptr, align 8
  store ptr %y, ptr %y2, align 8
  %t = alloca i32, align 4
  %x_load = load ptr, ptr %x1, align 8
  %0 = load i32, ptr %x_load, align 4
  store i32 %0, ptr %t, align 4
  %y_load = load ptr, ptr %y2, align 8
  %1 = load i32, ptr %y_load, align 4
  %x_load3 = load ptr, ptr %x1, align 8
  store i32 %1, ptr %x_load3, align 4
  %2 = load i32, ptr %t, align 4
  %y_load4 = load ptr, ptr %y2, align 8
  store i32 %2, ptr %y_load4, align 4
  ret void
}

define void @writeArray(ptr %msg, i32 %n, ptr %x) {
writeArray_entry:
  %msg1 = alloca ptr, align 8
  store ptr %msg, ptr %msg1, align 8
  %n2 = alloca i32, align 4
  store i32 %n, ptr %n2, align 4
  %x3 = alloca ptr, align 8
  store ptr %x, ptr %x3, align 8
  %i = alloca i32, align 4
  %msg_load = load ptr, ptr %msg1, align 8
  call void @writeString(ptr %msg_load)
  %int_const = alloca i32, align 4
  store i32 0, ptr %int_const, align 4
  %0 = load i32, ptr %int_const, align 4
  store i32 %0, ptr %i, align 4
  br label %cond

cond:                                             ; preds = %ifcont, %writeArray_entry
  %left_load = load i32, ptr %i, align 4
  %right_load = load i32, ptr %n2, align 4
  %lttmp = icmp slt i32 %left_load, %right_load
  %1 = zext i1 %lttmp to i32
  %while_cond = icmp ne i32 %1, 0
  br i1 %while_cond, label %loop, label %afterloop

loop:                                             ; preds = %cond
  %int_const4 = alloca i32, align 4
  store i32 0, ptr %int_const4, align 4
  %left_load5 = load i32, ptr %i, align 4
  %right_load6 = load i32, ptr %int_const4, align 4
  %gttmp = icmp sgt i32 %left_load5, %right_load6
  %2 = zext i1 %gttmp to i32
  %if_cond = icmp ne i32 %2, 0
  br i1 %if_cond, label %then, label %else

then:                                             ; preds = %loop
  %str_const_alloca = alloca [3 x i8], align 1
  call void @llvm.memcpy.p0.p0.i32(ptr align 1 %str_const_alloca, ptr align 1 @global_str, i32 3, i1 false)
  call void @writeString(ptr %str_const_alloca)
  br label %ifcont

else:                                             ; preds = %loop
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  %load_index = load i32, ptr %i, align 4
  %x_arrayptr = load ptr, ptr %x3, align 8
  %elementptr = getelementptr i32, ptr %x_arrayptr, i32 %load_index
  %writeInteger_arg = load i32, ptr %elementptr, align 4
  call void @writeInteger(i32 %writeInteger_arg)
  %int_const7 = alloca i32, align 4
  store i32 1, ptr %int_const7, align 4
  %left_load8 = load i32, ptr %i, align 4
  %right_load9 = load i32, ptr %int_const7, align 4
  %binop_tmp = alloca i32, align 4
  %addtmp = add i32 %left_load8, %right_load9
  store i32 %addtmp, ptr %binop_tmp, align 4
  %3 = load i32, ptr %binop_tmp, align 4
  store i32 %3, ptr %i, align 4
  br label %cond

afterloop:                                        ; preds = %cond
  %str_const_alloca10 = alloca [2 x i8], align 1
  call void @llvm.memcpy.p0.p0.i32(ptr align 1 %str_const_alloca10, ptr align 1 @global_str.2, i32 2, i1 false)
  call void @writeString(ptr %str_const_alloca10)
  ret void
}

; Function Attrs: argmemonly nocallback nofree nounwind willreturn
declare void @llvm.memcpy.p0.p0.i32(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i32, i1 immarg) #0

attributes #0 = { argmemonly nocallback nofree nounwind willreturn }
