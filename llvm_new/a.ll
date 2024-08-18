
@global_str = private unnamed_addr constant [9 x i8] c"correct\0A\00", align 1
@global_str.1 = private unnamed_addr constant [7 x i8] c"wrong\0A\00", align 1

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
  call void @comp()
  ret i32 0
}

define void @comp() {
comp_entry:
  %int_const = alloca i32, align 4
  store i32 5, ptr %int_const, align 4
  %int_const1 = alloca i32, align 4
  store i32 15, ptr %int_const1, align 4
  %compop_tmp = alloca i32, align 4
  %0 = load i32, ptr %int_const, align 4
  %1 = load i32, ptr %int_const1, align 4
  %gttmp = icmp sgt i32 %0, %1
  store i1 %gttmp, ptr %compop_tmp, align 1
  %2 = load i32, ptr %compop_tmp, align 4
  %if_cond = icmp ne i32 %2, 0
  br i1 %if_cond, label %then, label %else

then:                                             ; preds = %comp_entry
  %str_const_alloca = alloca [9 x i8], align 1
  call void @llvm.memcpy.p0.p0.i32(ptr align 1 %str_const_alloca, ptr align 1 @global_str, i32 9, i1 false)
  call void @writeString(ptr %str_const_alloca)
  br label %ifcont

else:                                             ; preds = %comp_entry
  %str_const_alloca2 = alloca [7 x i8], align 1
  call void @llvm.memcpy.p0.p0.i32(ptr align 1 %str_const_alloca2, ptr align 1 @global_str.1, i32 7, i1 false)
  call void @writeString(ptr %str_const_alloca2)
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  ret void
}

; Function Attrs: argmemonly nocallback nofree nounwind willreturn
declare void @llvm.memcpy.p0.p0.i32(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i32, i1 immarg) #0

attributes #0 = { argmemonly nocallback nofree nounwind willreturn }
