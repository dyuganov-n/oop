
import javax.print.attribute.HashAttributeSet;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;

public class MorseEncoder {
    private final Alphabet alphabet;

    public MorseEncoder(Alphabet alphabet){
        this.alphabet = alphabet;
    }



    public void encode(ArrayList<String> text, String resultFileName) throws NullPointerException, IOException {

        StringBuilder resultString = new StringBuilder();
        HashSet<StatCounter> statistics = new HashSet<StatCounter>();

        FileWriter encodeOut = new FileWriter(resultFileName);

        for(String str : text){
            for (Character character : str.toCharArray()){
                /*if(character.equals('\n')){
                    encodeOut.write('\n');
                    encodeOut.write(resultString.toString());
                    resultString.delete(0, resultString.length());
                    continue;
                }*/
                resultString.append(alphabet.getMorseCodeByChar(character));
                resultString.append(' ');

                if(!statistics.add(new StatCounter(character))){
                    for (StatCounter counter : statistics) {
                        if(counter.getSymbol().equals(character)){
                            counter.increaseCnt();
                        }
                    }
                }
            }
            String morseCodeSpace = "   ";
            encodeOut.write(resultString.toString() + morseCodeSpace);
            resultString.delete(0, resultString.length());
        }

        printStatsToFile("encode_stats.txt", statistics);

        encodeOut.close();

    }

    private void printStatsToFile(String fileName, HashSet<StatCounter> statistics) throws IOException{
        FileWriter statsOut = new FileWriter(fileName);

        for(StatCounter counter : statistics){
            statsOut.write(counter.getSymbol() + ' ' + counter.getCounter());
        }

        statsOut.close();
    }

}
