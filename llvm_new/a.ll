
@global_str = private unnamed_addr constant [24 x i8] c"Give the first integer:\00", align 1
@global_str.1 = private unnamed_addr constant [25 x i8] c"Give the second integer:\00", align 1
@global_str.2 = private unnamed_addr constant [33 x i8] c"\0AThe gcd you are looking for is \00", align 1

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
  %str_const_alloca = alloca [24 x i8], align 1
  call void @llvm.memcpy.p0.p0.i32(ptr align 1 %str_const_alloca, ptr align 1 @global_str, i32 24, i1 false)
  call void @writeString(ptr %str_const_alloca)
  %readInteger_ret = alloca i32, align 4
  %readInteger_call = call i32 @readInteger()
  store i32 %readInteger_call, ptr %readInteger_ret, align 4
  %0 = load i32, ptr %readInteger_ret, align 4
  store i32 %0, ptr %a, align 4
  %str_const_alloca1 = alloca [25 x i8], align 1
  call void @llvm.memcpy.p0.p0.i32(ptr align 1 %str_const_alloca1, ptr align 1 @global_str.1, i32 25, i1 false)
  call void @writeString(ptr %str_const_alloca1)
  %readInteger_ret2 = alloca i32, align 4
  %readInteger_call3 = call i32 @readInteger()
  store i32 %readInteger_call3, ptr %readInteger_ret2, align 4
  %1 = load i32, ptr %readInteger_ret2, align 4
  store i32 %1, ptr %b, align 4
  %str_const_alloca4 = alloca [33 x i8], align 1
  call void @llvm.memcpy.p0.p0.i32(ptr align 1 %str_const_alloca4, ptr align 1 @global_str.2, i32 33, i1 false)
  call void @writeString(ptr %str_const_alloca4)
  %find_gcd_arg = load i32, ptr %a, align 4
  %find_gcd_arg5 = load i32, ptr %b, align 4
  %find_gcd_ret = alloca i32, align 4
  %find_gcd_call = call i32 @find_gcd(i32 %find_gcd_arg, i32 %find_gcd_arg5)
  store i32 %find_gcd_call, ptr %find_gcd_ret, align 4
  %writeInteger_arg = load i32, ptr %find_gcd_ret, align 4
  call void @writeInteger(i32 %writeInteger_arg)
  %char_const = alloca i8, align 1
  store i8 10, ptr %char_const, align 1
  %writeChar_arg = load i8, ptr %char_const, align 1
  call void @writeChar(i8 %writeChar_arg)
  ret void
}

define i32 @find_gcd(i32 %a, i32 %b) {
find_gcd_entry:
  %a1 = alloca i32, align 4
  store i32 %a, ptr %a1, align 4
  %b2 = alloca i32, align 4
  store i32 %b, ptr %b2, align 4
  %i = alloca i32, align 4
  %left_val = load i32, ptr %a1, align 4
  %right_val = load i32, ptr %b2, align 4
  %gttmp = icmp sgt i32 %left_val, %right_val
  %0 = zext i1 %gttmp to i32
  %if_cond = icmp ne i32 %0, 0
  br i1 %if_cond, label %then, label %else

then:                                             ; preds = %find_gcd_entry
  %1 = load i32, ptr %a1, align 4
  store i32 %1, ptr %i, align 4
  br label %ifcont

else:                                             ; preds = %find_gcd_entry
  %2 = load i32, ptr %b2, align 4
  store i32 %2, ptr %i, align 4
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  br label %cond

cond:                                             ; preds = %ifcont18, %ifcont
  %int_const = alloca i32, align 4
  store i32 1, ptr %int_const, align 4
  %left_val3 = load i32, ptr %i, align 4
  %right_val4 = load i32, ptr %int_const, align 4
  %gttmp5 = icmp sgt i32 %left_val3, %right_val4
  %3 = zext i1 %gttmp5 to i32
  %while_cond = icmp ne i32 %3, 0
  br i1 %while_cond, label %loop, label %afterloop

loop:                                             ; preds = %cond
  %binop_tmp = alloca i32, align 4
  %4 = load i32, ptr %a1, align 4
  %5 = load i32, ptr %i, align 4
  %modtmp = srem i32 %4, %5
  store i32 %modtmp, ptr %binop_tmp, align 4
  %int_const6 = alloca i32, align 4
  store i32 0, ptr %int_const6, align 4
  %left_val7 = load i32, ptr %binop_tmp, align 4
  %right_val8 = load i32, ptr %int_const6, align 4
  %eqtmp = icmp eq i32 %left_val7, %right_val8
  %binop_tmp9 = alloca i32, align 4
  %6 = load i32, ptr %b2, align 4
  %7 = load i32, ptr %i, align 4
  %modtmp10 = srem i32 %6, %7
  store i32 %modtmp10, ptr %binop_tmp9, align 4
  %int_const11 = alloca i32, align 4
  store i32 0, ptr %int_const11, align 4
  %left_val12 = load i32, ptr %binop_tmp9, align 4
  %right_val13 = load i32, ptr %int_const11, align 4
  %eqtmp14 = icmp eq i32 %left_val12, %right_val13
  %andtmp = and i1 %eqtmp, %eqtmp14
  %8 = zext i1 %andtmp to i32
  %if_cond16 = icmp ne i32 %8, 0
  br i1 %if_cond16, label %then15, label %else17

then15:                                           ; preds = %loop
  %ret_val = load i32, ptr %i, align 4
  ret i32 %ret_val

else17:                                           ; preds = %loop
  br label %ifcont18

ifcont18:                                         ; preds = %else17
  %int_const19 = alloca i32, align 4
  store i32 1, ptr %int_const19, align 4
  %binop_tmp20 = alloca i32, align 4
  %9 = load i32, ptr %i, align 4
  %10 = load i32, ptr %int_const19, align 4
  %subtmp = sub i32 %9, %10
  store i32 %subtmp, ptr %binop_tmp20, align 4
  %11 = load i32, ptr %binop_tmp20, align 4
  store i32 %11, ptr %i, align 4
  br label %cond

afterloop:                                        ; preds = %cond
  %int_const21 = alloca i32, align 4
  store i32 1, ptr %int_const21, align 4
  %ret_val22 = load i32, ptr %int_const21, align 4
  ret i32 %ret_val22
}

; Function Attrs: argmemonly nocallback nofree nounwind willreturn
declare void @llvm.memcpy.p0.p0.i32(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i32, i1 immarg) #0

attributes #0 = { argmemonly nocallback nofree nounwind willreturn }
