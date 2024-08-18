localdefs
arg: ringstype: Int
arg: sourcetype: Array
arg: targettype: Array
arg: auxiliarytype: Array
localdefs
arg: sourcetype: Array
arg: targettype: Array
localdefs
Generating code for identifier NumberOfRings
Generating code for procedure call 
arg: rings
Generating code for identifier NumberOfRings
arg: source
Generating code for string constant "left"
arg: target
Generating code for string constant "right"
arg: auxiliary
Generating code for string constant "middle"
Function return type settled
Function call generated for void return type

@global_str = private unnamed_addr constant [7 x i8] c"\22left\22\00", align 1
@global_str.1 = private unnamed_addr constant [8 x i8] c"\22right\22\00", align 1
@global_str.2 = private unnamed_addr constant [9 x i8] c"\22middle\22\00", align 1

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
  call void @solve()
  ret i32 0
}

define void @solve() {
solve_entry:
  %NumberOfRings = alloca i32, align 4
  %i = alloca i32, align 4
  %int_const = alloca i32, align 4
  store i32 42, ptr %int_const, align 4
  %0 = load i32, ptr %int_const, align 4
  store i32 %0, ptr %NumberOfRings, align 4
  %hanoi_arg = load i32, ptr %NumberOfRings, align 4
  %str_const_alloca = alloca [7 x i8], align 1
  call void @llvm.memcpy.p0.p0.i32(ptr align 1 %str_const_alloca, ptr align 1 @global_str, i32 7, i1 false)
  %str_const_alloca1 = alloca [8 x i8], align 1
  call void @llvm.memcpy.p0.p0.i32(ptr align 1 %str_const_alloca1, ptr align 1 @global_str.1, i32 8, i1 false)
  %str_const_alloca2 = alloca [9 x i8], align 1
  call void @llvm.memcpy.p0.p0.i32(ptr align 1 %str_const_alloca2, ptr align 1 @global_str.2, i32 9, i1 false)
  call void @hanoi(i32 %hanoi_arg, ptr %str_const_alloca, ptr %str_const_alloca1, ptr %str_const_alloca2)
  ret void
}

define void @hanoi(i32 %rings, ptr %source, ptr %target, ptr %auxiliary) {
hanoi_entry:
  %rings1 = alloca i32, align 4
  store i32 %rings, ptr %rings1, align 4
  %source2 = alloca ptr, align 8
  store ptr %source, ptr %source2, align 8
  %target3 = alloca ptr, align 8
  store ptr %target, ptr %target3, align 8
  %auxiliary4 = alloca ptr, align 8
  store ptr %auxiliary, ptr %auxiliary4, align 8
  %i = alloca i32, align 4
  %t = alloca i8, align 1
  ret void
}

define void @move(ptr %source, ptr %target) {
move_entry:
  %source1 = alloca ptr, align 8
  store ptr %source, ptr %source1, align 8
  %target2 = alloca ptr, align 8
  store ptr %target, ptr %target2, align 8
  ret void
}

; Function Attrs: argmemonly nocallback nofree nounwind willreturn
declare void @llvm.memcpy.p0.p0.i32(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i32, i1 immarg) #0

attributes #0 = { argmemonly nocallback nofree nounwind willreturn }
