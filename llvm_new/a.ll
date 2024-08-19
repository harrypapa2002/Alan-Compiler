
@global_str = private unnamed_addr constant [39 x i8] c"Give a string with maximum length 30: \00", align 1
@global_str.1 = private unnamed_addr constant [23 x i8] c"\0AIs not palindrome...\0A\00", align 1
@global_str.2 = private unnamed_addr constant [19 x i8] c"\0AIs palindrome...\0A\00", align 1

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
  call void @cancer()
  ret i32 0
}

define void @cancer() {
cancer_entry:
  %n = alloca i32, align 4
  %source1 = alloca [31 x i8], align 1
  %str_const_alloca = alloca [39 x i8], align 1
  call void @llvm.memcpy.p0.p0.i32(ptr align 1 %str_const_alloca, ptr align 1 @global_str, i32 39, i1 false)
  call void @writeString(ptr %str_const_alloca)
  %int_const = alloca i32, align 4
  store i32 30, ptr %int_const, align 4
  %readString_arg = load i32, ptr %int_const, align 4
  call void @readString(i32 %readString_arg, ptr %source1)
  %int_const1 = alloca i32, align 4
  store i32 0, ptr %int_const1, align 4
  %0 = load i32, ptr %int_const1, align 4
  store i32 %0, ptr %n, align 4
  br label %cond

cond:                                             ; preds = %loop, %cancer_entry
  %load_index = load i32, ptr %n, align 4
  %elementptr = getelementptr [31 x i8], ptr %source1, i32 0, i32 %load_index
  %char_const = alloca i8, align 1
  store i8 0, ptr %char_const, align 1
  %left_load = load i8, ptr %elementptr, align 1
  %right_load = load i8, ptr %char_const, align 1
  %neqtmp = icmp ne i8 %left_load, %right_load
  %1 = zext i1 %neqtmp to i32
  %while_cond = icmp ne i32 %1, 0
  br i1 %while_cond, label %loop, label %afterloop

loop:                                             ; preds = %cond
  %int_const2 = alloca i32, align 4
  store i32 1, ptr %int_const2, align 4
  %left_load3 = load i32, ptr %n, align 4
  %right_load4 = load i32, ptr %int_const2, align 4
  %binop_tmp = alloca i32, align 4
  %addtmp = add i32 %left_load3, %right_load4
  store i32 %addtmp, ptr %binop_tmp, align 4
  %2 = load i32, ptr %binop_tmp, align 4
  store i32 %2, ptr %n, align 4
  br label %cond

afterloop:                                        ; preds = %cond
  %is_it_arg = load i32, ptr %n, align 4
  %is_it_call = call i32 @is_it(i32 %is_it_arg, ptr %source1)
  %int_const5 = alloca i32, align 4
  store i32 1, ptr %int_const5, align 4
  %right_load6 = load i32, ptr %int_const5, align 4
  %eqtmp = icmp eq i32 %is_it_call, %right_load6
  %3 = zext i1 %eqtmp to i32
  %if_cond = icmp ne i32 %3, 0
  br i1 %if_cond, label %then, label %else

then:                                             ; preds = %afterloop
  %str_const_alloca7 = alloca [23 x i8], align 1
  call void @llvm.memcpy.p0.p0.i32(ptr align 1 %str_const_alloca7, ptr align 1 @global_str.1, i32 23, i1 false)
  call void @writeString(ptr %str_const_alloca7)
  br label %ifcont

else:                                             ; preds = %afterloop
  %str_const_alloca8 = alloca [19 x i8], align 1
  call void @llvm.memcpy.p0.p0.i32(ptr align 1 %str_const_alloca8, ptr align 1 @global_str.2, i32 19, i1 false)
  call void @writeString(ptr %str_const_alloca8)
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  ret void
}

define i32 @is_it(i32 %n, ptr %source) {
is_it_entry:
  %n1 = alloca i32, align 4
  store i32 %n, ptr %n1, align 4
  %source2 = alloca ptr, align 8
  store ptr %source, ptr %source2, align 8
  %i = alloca i32, align 4
  %int_const = alloca i32, align 4
  store i32 1, ptr %int_const, align 4
  %left_load = load i32, ptr %n1, align 4
  %right_load = load i32, ptr %int_const, align 4
  %binop_tmp = alloca i32, align 4
  %subtmp = sub i32 %left_load, %right_load
  store i32 %subtmp, ptr %binop_tmp, align 4
  %0 = load i32, ptr %binop_tmp, align 4
  store i32 %0, ptr %n1, align 4
  %int_const3 = alloca i32, align 4
  store i32 0, ptr %int_const3, align 4
  %1 = load i32, ptr %int_const3, align 4
  store i32 %1, ptr %i, align 4
  br label %cond

cond:                                             ; preds = %ifcont, %is_it_entry
  %int_const4 = alloca i32, align 4
  store i32 2, ptr %int_const4, align 4
  %left_load5 = load i32, ptr %n1, align 4
  %right_load6 = load i32, ptr %int_const4, align 4
  %binop_tmp7 = alloca i32, align 4
  %divtmp = sdiv i32 %left_load5, %right_load6
  store i32 %divtmp, ptr %binop_tmp7, align 4
  %int_const8 = alloca i32, align 4
  store i32 1, ptr %int_const8, align 4
  %left_load9 = load i32, ptr %binop_tmp7, align 4
  %right_load10 = load i32, ptr %int_const8, align 4
  %binop_tmp11 = alloca i32, align 4
  %addtmp = add i32 %left_load9, %right_load10
  store i32 %addtmp, ptr %binop_tmp11, align 4
  %left_load12 = load i32, ptr %i, align 4
  %right_load13 = load i32, ptr %binop_tmp11, align 4
  %ltetmp = icmp sle i32 %left_load12, %right_load13
  %2 = zext i1 %ltetmp to i32
  %while_cond = icmp ne i32 %2, 0
  br i1 %while_cond, label %loop, label %afterloop

loop:                                             ; preds = %cond
  %load_index = load i32, ptr %i, align 4
  %source_arrayptr = load ptr, ptr %source2, align 8
  %elementptr = getelementptr i8, ptr %source_arrayptr, i32 %load_index
  %left_load14 = load i32, ptr %n1, align 4
  %right_load15 = load i32, ptr %i, align 4
  %binop_tmp16 = alloca i32, align 4
  %subtmp17 = sub i32 %left_load14, %right_load15
  store i32 %subtmp17, ptr %binop_tmp16, align 4
  %load_index18 = load i32, ptr %binop_tmp16, align 4
  %source_arrayptr19 = load ptr, ptr %source2, align 8
  %elementptr20 = getelementptr i8, ptr %source_arrayptr19, i32 %load_index18
  %left_load21 = load i8, ptr %elementptr, align 1
  %right_load22 = load i8, ptr %elementptr20, align 1
  %neqtmp = icmp ne i8 %left_load21, %right_load22
  %3 = zext i1 %neqtmp to i32
  %if_cond = icmp ne i32 %3, 0
  br i1 %if_cond, label %then, label %else

then:                                             ; preds = %loop
  %int_const23 = alloca i32, align 4
  store i32 1, ptr %int_const23, align 4
  %ret_val = load i32, ptr %int_const23, align 4
  ret i32 %ret_val

else:                                             ; preds = %loop
  br label %ifcont

ifcont:                                           ; preds = %else
  %int_const24 = alloca i32, align 4
  store i32 1, ptr %int_const24, align 4
  %left_load25 = load i32, ptr %i, align 4
  %right_load26 = load i32, ptr %int_const24, align 4
  %binop_tmp27 = alloca i32, align 4
  %addtmp28 = add i32 %left_load25, %right_load26
  store i32 %addtmp28, ptr %binop_tmp27, align 4
  %4 = load i32, ptr %binop_tmp27, align 4
  store i32 %4, ptr %i, align 4
  br label %cond

afterloop:                                        ; preds = %cond
  %int_const29 = alloca i32, align 4
  store i32 0, ptr %int_const29, align 4
  %ret_val30 = load i32, ptr %int_const29, align 4
  ret i32 %ret_val30
}

; Function Attrs: argmemonly nocallback nofree nounwind willreturn
declare void @llvm.memcpy.p0.p0.i32(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i32, i1 immarg) #0

attributes #0 = { argmemonly nocallback nofree nounwind willreturn }
