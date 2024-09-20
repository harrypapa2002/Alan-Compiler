
%reverse_closure = type { ptr, ptr }

@global_str = private unnamed_addr constant [5 x i8] c"k = \00", align 1
@global_str.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_str.3 = private unnamed_addr constant [14 x i8] c"\0A!dlrow olleH\00", align 1

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
  %r = alloca [32 x i8], align 1
  %k = alloca i32, align 4
  %reverse_closure_instance = alloca %reverse_closure, align 8
  %k_ptr = getelementptr inbounds %reverse_closure, ptr %reverse_closure_instance, i32 0, i32 0
  store ptr %k, ptr %k_ptr, align 8
  %r_ptr = getelementptr inbounds %reverse_closure, ptr %reverse_closure_instance, i32 0, i32 1
  store ptr %r, ptr %r_ptr, align 8
  call void @reverse(ptr %reverse_closure_instance, ptr @global_str.3)
  call void @writeString(ptr %r)
  ret void
}

define void @reverse(ptr %closure, ptr %s) {
reverse_entry:
  %k_ptr = getelementptr inbounds %reverse_closure, ptr %closure, i32 0, i32 0
  %k = load ptr, ptr %k_ptr, align 8
  %k1 = alloca ptr, align 8
  store ptr %k, ptr %k1, align 8
  %r_ptr = getelementptr inbounds %reverse_closure, ptr %closure, i32 0, i32 1
  %r = load ptr, ptr %r_ptr, align 8
  %r2 = alloca ptr, align 8
  store ptr %r, ptr %r2, align 8
  %s3 = alloca ptr, align 8
  store ptr %s, ptr %s3, align 8
  %i = alloca i32, align 4
  %l = alloca i32, align 4
  %s_load = load ptr, ptr %s3, align 8
  %strlen_call = call i32 @strlen(ptr %s_load)
  store i32 %strlen_call, ptr %l, align 4
  store i32 0, ptr %i, align 4
  br label %cond

cond:                                             ; preds = %loop, %reverse_entry
  %left_load = load i32, ptr %i, align 4
  %right_load = load i32, ptr %l, align 4
  %lttmp = icmp slt i32 %left_load, %right_load
  %0 = zext i1 %lttmp to i32
  %while_cond = icmp ne i32 %0, 0
  br i1 %while_cond, label %loop, label %afterloop

loop:                                             ; preds = %cond
  %left_load4 = load i32, ptr %l, align 4
  %right_load5 = load i32, ptr %i, align 4
  %subtmp = sub i32 %left_load4, %right_load5
  %subtmp6 = sub i32 %subtmp, 1
  %s_arrayptr = load ptr, ptr %s3, align 8
  %elementptr = getelementptr i8, ptr %s_arrayptr, i32 %subtmp6
  %load_rvalue = load i8, ptr %elementptr, align 1
  %load_index = load i32, ptr %i, align 4
  %r_arrayptr = load ptr, ptr %r2, align 8
  %elementptr7 = getelementptr i8, ptr %r_arrayptr, i32 %load_index
  store i8 %load_rvalue, ptr %elementptr7, align 1
  %left_load8 = load i32, ptr %i, align 4
  %addtmp = add i32 %left_load8, 1
  store i32 %addtmp, ptr %i, align 4
  br label %cond

afterloop:                                        ; preds = %cond
  %load_index9 = load i32, ptr %i, align 4
  %r_arrayptr10 = load ptr, ptr %r2, align 8
  %elementptr11 = getelementptr i8, ptr %r_arrayptr10, i32 %load_index9
  store i8 0, ptr %elementptr11, align 1
  %k_load = load ptr, ptr %k1, align 8
  store i32 5, ptr %k_load, align 4
  call void @writeString(ptr @global_str)
  %k_load12 = load ptr, ptr %k1, align 8
  %writeInteger_arg = load i32, ptr %k_load12, align 4
  call void @writeInteger(i32 %writeInteger_arg)
  call void @writeString(ptr @global_str.2)
  ret void
}
