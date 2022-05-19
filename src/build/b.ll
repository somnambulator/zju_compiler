; ModuleID = 'Code Gen'
source_filename = "Code Gen"

@gi = global i32 0
@gf = global double 0.000000e+00
@printfomat = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@printfomat.1 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@printfomat.2 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@printfomat.3 = private unnamed_addr constant [4 x i8] c"%f\0A\00", align 1

define void @main() {
entry:
  %b = alloca i32, align 4
  %a = alloca i32, align 4
  store i32 0, i32* %a, align 4
  store i32 1, i32* %a, align 4
  store i32 0, i32* %b, align 4
  store i32 1, i32* %b, align 4
  %b1 = load i32, i32* %b, align 4
  %printtmp = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printfomat, i32 0, i32 0), i32 %b1)
  %a2 = load i32, i32* %a, align 4
  %printtmp3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printfomat.1, i32 0, i32 0), i32 %a2)
  %gi = load i32, i32* @gi, align 4
  %addtmp = add i32 %gi, 7
  %printtmp4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printfomat.2, i32 0, i32 0), i32 %addtmp)
  %gf = load double, double* @gf, align 8
  %addtmp5 = fadd double %gf, 0x401ECCCCC0000000
  %printtmp6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @printfomat.3, i32 0, i32 0), double %addtmp5)
  ret void
}

declare i32 @printf(i8*, ...)
