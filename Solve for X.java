// Solve for X program, Marz COSC 101, 11.12.2023
// Clark Kirby
// No outside sources used

import java.util.Random;
import java.util.Scanner;

class arrays {
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter random seed: ");
        seed = sc.nextInt();

        int size;
        int minCoeff;
        int maxCoeff;
        int minVal;
        int maxVal;
        int minEquals;
        int maxEquals;

        do {
            System.out.printf("How many problems do you want? ");
            size = sc.nextInt();
        } while (size < MIN_SIZE || size > MAX_SIZE); // making sure the desired size is between the already declaired
                                                      // maximum and minimum size.

        // from line 24 to 60, it just intakes all the values and makes sure they are
        // within the desired ranges
        do {
            System.out.printf("Enter minimum coefficient: ");
            minCoeff = sc.nextInt();
        } while (minCoeff < MIN_COEFF || minCoeff > MAX_COEFF);

        do {
            System.out.printf("Enter maximum coefficient: ");
            maxCoeff = sc.nextInt();
        } while (maxCoeff < minCoeff || maxCoeff > MAX_COEFF);

        do {
            System.out.printf("Enter minimum value: ");
            minVal = sc.nextInt();
        } while (minVal < MIN_VAL || minVal > MAX_VAL);

        do {
            System.out.printf("Enter maximum value: ");
            maxVal = sc.nextInt();
        } while (maxVal < minVal || maxVal > MAX_VAL);

        do {
            System.out.printf("Enter minimum equals: ");
            minEquals = sc.nextInt();
        } while (minEquals < MIN_EQ || minEquals > MAX_EQ);

        do {
            System.out.printf("Enter maximum equals: ");
            maxEquals = sc.nextInt();
        } while (maxEquals < minEquals || maxEquals > MAX_EQ);

        // generates the random arrays from the newly accepted values for the mininum
        // and maximum values
        int coeff[] = generateRandomArray(size, minCoeff, maxCoeff);
        int value[] = generateRandomArray(size, minVal, maxVal);
        int opperation[] = generateRandomArray(size, 0, 1);
        int equals[] = generateRandomArray(size, minEquals, maxEquals);
        double x[] = generateAnswers(coeff, value, opperation, equals);
        double[] response = new double[size];
        String[] verdict = new String[size];

        int num_correct = 0;
        int i;
        for (i = 0; i < size; i += 1) {
            generateAnswer(coeff[i], value[i], opperation[i], equals[i]);
            if (opperation[i] == 0) { // the if statement checks if the opperation is plus or minus, and then puts the
                                      // values in the proper equation. if opperation is zero, we add the value, and
                                      // vice versa
                System.out.printf("%dx + %d = %d%n", coeff[i], value[i], equals[i]);
            } else {
                System.out.printf("%dx - %d = %d%n", coeff[i], value[i], equals[i]);
            }
            double answer;
            System.out.print("What is x? ");
            while (!sc.hasNextDouble()) {
                System.out.println("Invalid Answer.");
                System.out.print("What is x? ");
                sc.next();
            }
            answer = sc.nextDouble();
            response[i] = answer;

            if (compareAnswer(answer, x[i])) { // created an array for correct or incorrect responses for ease of use
                                               // later when we have to display the correct/incorrect response in the
                                               // output.
                num_correct += 1;
                verdict[i] = "CORRECT";
            } else {
                verdict[i] = "INCORRECT";
            }
        }
        sc.close(); // for myself: always close the scanner. the last time the scanner is used is
                    // within the previous for loop.

        int num_incorrect = size - num_correct;
        double accuracy = (num_correct / size) * 100; // calculates the amount of problems correct and converts it to a
                                                      // percentage to display to the user

        int j;
        for (j = 0; j < size; j += 1) {
            String str_equation; // the string str_equation will be used for ease of displaying the equation back
                                 // to the user within a specified field.
            if (opperation[j] == 0) {
                str_equation = coeff[j] + "x + " + value[j] + " = " + equals[j]; // puts the equation in a singular
                                                                                 // string
            } else {
                str_equation = coeff[j] + "x - " + value[j] + " = " + equals[j];
            }

            System.out.printf("%-20s x = %-10.3f %s%n", str_equation, x[j], verdict[j]); // prints the equation, the
                                                                                         // true answer, and whether the
                                                                                         // user was correct or not.
        }

        System.out.printf("Num correct   = %d%n", num_correct);
        System.out.printf("Num incorrect = %d%n", num_incorrect);
        System.out.printf("Your score    = %.0f%%%n", accuracy);

    }

    static final int MIN_SIZE = 1;
    static final int MAX_SIZE = 10;

    static final int MIN_COEFF = 1;
    static final int MAX_COEFF = 5;

    static final int MIN_VAL = -100000;
    static final int MAX_VAL = 100000;

    static final int MIN_EQ = -100000;
    static final int MAX_EQ = 100000;

    static final double MY_EPSILON = 0.01;

    static int seed;

    static int[] generateRandomArray(int size, int minValue, int maxValue) {
        int i;
        int[] arr = new int[size];
        Random rand = new Random(seed);

        for (i = 0; i < size; i++) {
            int random_int = rand.nextInt(minValue, maxValue + 1); // the max value is exclusive, so we have to add one
                                                                   // to make it inclusive
            arr[i] = random_int;
        }
        return arr;
    }

    static double generateAnswer(int coeff, int value, int opperation, int equal) {
        double answer;

        if (opperation == 0) { // once again seperates by the opperation and uses the correct opperation for
                               // which randomly assigned opperation
            answer = ((double) equal - (double) value) / (double) coeff; // this algebraicly solves the equation by
                                                                         // isolating the x-variable to one side and
                                                                         // then dividing by the coefficient.
        } else {
            answer = ((double) equal + (double) value) / (double) coeff;
        }
        return answer;
    }

    static double[] generateAnswers(int[] coeffs, int[] values, int[] opperation, int[] equals) { // all this method
                                                                                                  // does is uses the
                                                                                                  // generateAnswer(singular)
                                                                                                  // method and calls it
                                                                                                  // for every index of
                                                                                                  // the size
        int i;
        double[] solutions = new double[coeffs.length];

        for (i = 0; i < coeffs.length; i += 1) {
            double answer = generateAnswer(coeffs[i], values[i], opperation[i], equals[i]);
            solutions[i] = answer;
        }
        return solutions;
    }

    static boolean compareAnswer(double answer, double guess) {
        if (Math.abs(answer - guess) > MY_EPSILON) { // this checks the difference between the solution and the guessed
                                                     // solution and makes sure its within the epsilon
            return false; // answer is wrong :(
        } else {
            return true; // answer is true
        }
    }
}