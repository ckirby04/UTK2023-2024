// Clark Kirby Taylor Series Project
// 10/28/2023, COSC 101 Marz
// no outside sources used.

import java.util.Scanner;
class taylorseries {

public static void main(String[] args){
Scanner sc = new Scanner(System.in);

boolean valid = true;
int n = 0;

System.out.print("Enter x: ");
double x = sc.nextDouble();

while(valid){           //while loop to repeat the input process until a valid input is recieved
    System.out.print("Enter number of iteraitons: ");
    n = sc.nextInt();
    sc.close();
    if(n >= 1 && n <= 10000){
        valid = false;
    }
}

double taylor = (taylor(x, n));
double exp = Math.exp(x);

double error = (1- (taylor / exp)) * 100; // computes the % difference between the assumed taylor series and the true function

System.out.printf("TAYLOR: %.3f, %.3f, %.0f%%", taylor, exp, error);


}

static double taylor_step(double x, int f){

    double numerator = Math.pow(x, f);
    double denomenator = 1;
    for(int i = 1; i <= f; i++){    // factorial - multiplies a number by all the numbers that came before it until zero.
        denomenator *= i;
    }
    double z;

    z = numerator / denomenator;

    return z;
}



static double taylor(double x, int n){
    int f;
    double total = 0;
    for(f = 0; f <= n; f += 1){         // loop to caclulate every taylor series for n to zero
        double partial = taylor_step(x, f); // this computes the taylor series at f as f increases to n, like how the function computes.
        total += partial;
    }

    return total;
}
}