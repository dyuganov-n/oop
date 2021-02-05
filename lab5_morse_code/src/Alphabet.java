import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class Alphabet {
    private Map<Character, String> charToMorse = null;
    private Map<String,Character> morseToChar = null;

    public Alphabet(String fileName) throws java.io.IOException {
        final int expectedSpacePos = 1;

        BufferedReader in = new BufferedReader(new FileReader(fileName));
        charToMorse = new HashMap<Character, String>();
        morseToChar = new HashMap<String, Character>();

        String str;
        while((str = in.readLine()) != null){
            if(str.indexOf(' ') != expectedSpacePos || str.isEmpty()){
                throw new IOException("Alphabet file has wrong format");
            }
            String[] splitStr = str.split(" ");
            charToMorse.put(str.charAt(0), splitStr[1]);
            morseToChar.put(splitStr[1], str.charAt(0));
        }

        in.close();

        if(charToMorse.isEmpty() || morseToChar.isEmpty()) {
            throw new IOException("Alphabet file is empty, nothing to do there");
        }
    }

    public String getMorseCodeByChar(Character character) {
        return charToMorse.get(character);
    }

    public Character getCharByMorseCode(String morseCode) {
        return morseToChar.get(morseCode);
    }
}
