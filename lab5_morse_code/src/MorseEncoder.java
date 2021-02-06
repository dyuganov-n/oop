import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

public class MorseEncoder {
    private final Alphabet alphabet;

    public MorseEncoder(Alphabet alphabet){
        this.alphabet = alphabet;
    }

    public void encode(ArrayList<String> text, String resultFileName) throws NullPointerException, IOException {
        StringBuilder resultString = new StringBuilder();
        StatCounter statCounter = new StatCounter();

        try(FileWriter encodeOut = new FileWriter(resultFileName)) {
            for(String str : text){
                for (Character character : str.toCharArray()){
                    resultString.append(alphabet.getMorseCodeByChar(character).toString()).append(" ");
                    statCounter.add(character);
                }
                String morseCodeSpace = "   ";
                encodeOut.write(resultString.toString() + morseCodeSpace);
                resultString.delete(0, resultString.length());
            }
        }
        statCounter.printToFile("encode_stats.txt");
    }

}
