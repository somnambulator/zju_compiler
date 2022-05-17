; ModuleID = 'Code Gen'
source_filename = "Code Gen"

@printfomat = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@printfomat.1 = private unnamed_addr constant [4 x i8] c"%f\0A\00", align 1
@printfomat.2 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@printfomat.3 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@printfomat.4 = private unnamed_addr constant [4 x i8] c"%f\0A\00", align 1
@printfomat.5 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@printfomat.6 = private unnamed_addr constant [4 x i8] c"%f\0A\00", align 1

define void @foo(double %b, i32 %a) {
entry:
  %a2 = alloca i32, align 4
  %b1 = alloca double, align 8
  store double %b, double* %b1, align 8
  store i32 %a, i32* %a2, align 4
  %a3 = load i32, i32* %a2, align 4
  %printtmp = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printfomat, i32 0, i32 0), i32 %a3)
  %b4 = load double, double* %b1, align 8
  %printtmp5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printfomat.1, i32 0, i32 0), double %b4)
  ret void
}

declare i32 @printf(i8*, ...)

define i32 @main() {
entry:
  %c = alloca double, align 8
  %b = alloca i32, align 4
  %a = alloca i32, align 4
  store i32 0, i32* %a, align 4
  store i32 1, i32* %a, align 4
  store i32 0, i32* %b, align 4
  store i32 2, i32* %b, align 4
  store double 0.000000e+00, double* %c, align 8
  store double 1.500000e+00, double* %c, align 8
  %printtmp = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printfomat.2, i32 0, i32 0), i32 1)
  %printtmp1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printfomat.3, i32 0, i32 0), i32 2)
  %printtmp2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printfomat.4, i32 0, i32 0), double 0x407B0199A0000000)
  store i32 100, i32* %a, align 4
  store i32 200, i32* %a, align 4
  store i32 101, i32* %a, align 4
  store i32 200, i32* %a, align 4
  store i32 50, i32* %a, align 4
  store i32 1501, i32* %a, align 4
  %b3 = load i32, i32* %b, align 4
  %addtmp = add i32 %b3, 1
  store i32 %addtmp, i32* %a, align 4
  %b4 = load i32, i32* %b, align 4
  %printtmp5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printfomat.5, i32 0, i32 0), i32 %b4)
  store double 2.500000e+00, double* %c, align 8
  %c6 = load double, double* %c, align 8
  %printtmp7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printfomat.6, i32 0, i32 0), double %c6)
  %c8 = load double, double* %c, align 8
  %a9 = load i32, i32* %a, align 4
  call void @foo(double %c8, i32 %a9)
  ret i32 0
}
