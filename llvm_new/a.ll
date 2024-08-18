
@global_str = private unnamed_addr constant [25 x i8] c"Give the first integer: \00", align 1
@global_str.1 = private unnamed_addr constant [26 x i8] c"Give the second integer: \00", align 1
@global_str.2 = private unnamed_addr constant [34 x i8] c"\\nThe gcd you are looking for is \00", align 1

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
  call void @gcd()
  ret i32 0
}

define void @gcd() {
gcd_entry:
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %str_const_alloca = alloca [25 x i8], align 1
  call void @llvm.memcpy.p0.p0.i32(ptr align 1 %str_const_alloca, ptr align 1 @global_str, i32 25, i1 false)
  call void @writeString(ptr %str_const_alloca)
  %readInteger_ret = alloca i32, align 4
  %readInteger_call = call i32 @readInteger()
  store i32 %readInteger_call, ptr %readInteger_ret, align 4
  %0 = load i32, ptr %readInteger_ret, align 4
  store i32 %0, ptr %a, align 4
  %str_const_alloca1 = alloca [26 x i8], align 1
  call void @llvm.memcpy.p0.p0.i32(ptr align 1 %str_const_alloca1, ptr align 1 @global_str.1, i32 26, i1 false)
  call void @writeString(ptr %str_const_alloca1)
  %readInteger_ret2 = alloca i32, align 4
  %readInteger_call3 = call i32 @readInteger()
  store i32 %readInteger_call3, ptr %readInteger_ret2, align 4
  %1 = load i32, ptr %readInteger_ret2, align 4
  store i32 %1, ptr %b, align 4
  %str_const_alloca4 = alloca [34 x i8], align 1
  call void @llvm.memcpy.p0.p0.i32(ptr align 1 %str_const_alloca4, ptr align 1 @global_str.2, i32 34, i1 false)
  call void @writeString(ptr %str_const_alloca4)
  %find_gcd_arg = load i32, ptr %a, align 4
  %find_gcd_arg5 = load i32, ptr %b, align 4
  %find_gcd_ret = alloca i32, align 4
  %find_gcd_call = call i32 @find_gcd(i32 %find_gcd_arg, i32 %find_gcd_arg5)
  store i32 %find_gcd_call, ptr %find_gcd_ret, align 4
  %writeInteger_arg = load i32, ptr %find_gcd_ret, align 4
  call void @writeInteger(i32 %writeInteger_arg)
  ret void
}

define i32 @find_gcd(i32 %a, i32 %b) {
find_gcd_entry:
  %a1 = alloca i32, align 4
  store i32 %a, ptr %a1, align 4
  %b2 = alloca i32, align 4
  store i32 %b, ptr %b2, align 4
  %i = alloca i32, align 4
  %compop_tmp = alloca i32, align 4
  %0 = load i32, ptr %a1, align 4
  %1 = load i32, ptr %b2, align 4
  %gttmp = icmp sgt i32 %0, %1
  store i1 %gttmp, ptr %compop_tmp, align 1
  %2 = load i32, ptr %compop_tmp, align 4
  %if_cond = icmp ne i32 %2, 0
  br i1 %if_cond, label %then, label %else

then:                                             ; preds = %find_gcd_entry
  %3 = load i32, ptr %a1, align 4
  store i32 %3, ptr %i, align 4
  br label %ifcont

else:                                             ; preds = %find_gcd_entry
  %4 = load i32, ptr %b2, align 4
  store i32 %4, ptr %i, align 4
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  br label %cond

cond:                                             ; preds = %ifcont15, %ifcont
  %int_const = alloca i32, align 4
  store i32 1, ptr %int_const, align 4
  %compop_tmp3 = alloca i32, align 4
  %5 = load i32, ptr %i, align 4
  %6 = load i32, ptr %int_const, align 4
  %gttmp4 = icmp sgt i32 %5, %6
  store i1 %gttmp4, ptr %compop_tmp3, align 1
  %load_cond = load i32, ptr %compop_tmp3, align 4
  %while_cond = icmp ne i32 %load_cond, 0
  br i1 %while_cond, label %loop, label %afterloop

loop:                                             ; preds = %cond
  %binop_tmp = alloca i32, align 4
  %7 = load i32, ptr %a1, align 4
  %8 = load i32, ptr %i, align 4
  %modtmp = srem i32 %7, %8
  store i32 %modtmp, ptr %binop_tmp, align 4
  %int_const5 = alloca i32, align 4
  store i32 0, ptr %int_const5, align 4
  %compop_tmp6 = alloca i32, align 4
  %9 = load i32, ptr %binop_tmp, align 4
  %10 = load i32, ptr %int_const5, align 4
  %eqtmp = icmp eq i32 %9, %10
  store i1 %eqtmp, ptr %compop_tmp6, align 1
  %binop_tmp7 = alloca i32, align 4
  %11 = load i32, ptr %b2, align 4
  %12 = load i32, ptr %i, align 4
  %modtmp8 = srem i32 %11, %12
  store i32 %modtmp8, ptr %binop_tmp7, align 4
  %int_const9 = alloca i32, align 4
  store i32 0, ptr %int_const9, align 4
  %compop_tmp10 = alloca i32, align 4
  %13 = load i32, ptr %binop_tmp7, align 4
  %14 = load i32, ptr %int_const9, align 4
  %eqtmp11 = icmp eq i32 %13, %14
  store i1 %eqtmp11, ptr %compop_tmp10, align 1
  %boolop_tmp = alloca i32, align 4
  %15 = load i32, ptr %compop_tmp6, align 4
  %16 = load i32, ptr %compop_tmp10, align 4
  %andtmp = and i32 %15, %16
  store i32 %andtmp, ptr %boolop_tmp, align 4
  %17 = load i32, ptr %boolop_tmp, align 4
  %if_cond12 = icmp ne i32 %17, 0
  br i1 %if_cond12, label %then13, label %else14

then13:                                           ; preds = %loop
  %ret_val = load i32, ptr %i, align 4
  ret i32 %ret_val

else14:                                           ; preds = %loop
  br label %ifcont15

ifcont15:                                         ; preds = %else14
  %int_const16 = alloca i32, align 4
  store i32 1, ptr %int_const16, align 4
  %binop_tmp17 = alloca i32, align 4
  %18 = load i32, ptr %i, align 4
  %19 = load i32, ptr %int_const16, align 4
  %subtmp = sub i32 %18, %19
  store i32 %subtmp, ptr %binop_tmp17, align 4
  %20 = load i32, ptr %binop_tmp17, align 4
  store i32 %20, ptr %i, align 4
  br label %cond

afterloop:                                        ; preds = %cond
  %int_const18 = alloca i32, align 4
  store i32 1, ptr %int_const18, align 4
  %ret_val19 = load i32, ptr %int_const18, align 4
  ret i32 %ret_val19
}

; Function Attrs: argmemonly nocallback nofree nounwind willreturn
declare void @llvm.memcpy.p0.p0.i32(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i32, i1 immarg) #0

attributes #0 = { argmemonly nocallback nofree nounwind willreturn }
