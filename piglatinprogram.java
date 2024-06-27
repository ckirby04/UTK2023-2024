// Pig Latin Program, Mr. Marz, COSC 101, 10.22.2023
// Clark Kirby 
// No outside sources used.


import java.util.Scanner;

class piglatin {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter Sentence('quit' to quit):");
        String sentence = sc.nextLine();
        sc.close();

        if(sentence.equalsIgnoreCase("quit")){
            return;
        }

        System.out.print(parse_line(sentence));

    }
    

        
    static final char[] vowels = {'A', 'a', 'E', 'e', 'O', 'o', 'U', 'u', 'I', 'i', 'Y', 'y'};

    static boolean vowel_check(char letter){

        int i;
        for (i = 0;i < vowels.length;i += 1) {
            if (letter == vowels[i]) {
                return true;
            }
         }
        return false;
        }


    static String translate(String word){
        StringBuilder build = new StringBuilder();
        build.append(word);
        char firstLetter = word.charAt(0);
        int f = 0;

        if(vowel_check(firstLetter)){       // if the word startes with a vowel, all we have to do is add yay to the end
            build.append("yay");
            String result = build.toString();
            return result;
            }

        else{
            char letter = word.charAt(f);       // this finds the first value at which a vowel is present, since we have to remove all letters before the first vowel
            while(vowel_check(letter)){
                f+=1;
            }

            String section = word.substring(0, f+1);

            build.append(section + "ay");
            build.delete(0, f+1);       // deletes the first letters up until the first vowel
            String result = build.toString();
            return result;

        }
    }
    
     static String parse_line(String line){
            String[] words = line.split(" "); // splits the line into individual string words into an array
            int i;
            StringBuilder finalString = new StringBuilder();
            for (i = 0;i < words.length;i += 1){        // goes through the array and translates each individual word and puts it in a final string to be returned back out 
                String result = translate(words[i]);
                finalString.append(result + " ");
            }
            return finalString.toString();
}
}

    

