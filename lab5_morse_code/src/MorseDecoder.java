
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

public class MorseDecoder {
    private final Alphabet alphabet;
    public MorseDecoder(Alphabet alphabet){
        this.alphabet = alphabet;
    }

    public void decode(ArrayList<String> text, String resultFileName) throws NullPointerException, IOException {
        String morseCodeSpace = "   ";

        StringBuilder resultString = new StringBuilder();
        Set<StatCounter> statistics = new HashSet<StatCounter>();

        try (FileWriter decodeOut = new FileWriter(resultFileName)) {
            for(String str : text) {
                for (String character : str.split(" ")) {
                    resultString.append(alphabet.getCharByMorseCode(character));
                    if(!statistics.add(new StatCounter(alphabet.getCharByMorseCode(character)))){
                        for (StatCounter counter : statistics) {
                            if(counter.getSymbol().equals(alphabet.getCharByMorseCode(character))){
                                counter.increaseCnt();
                            }
                        }
                    }
                }
                resultString.append(' ');
            }
            decodeOut.write(resultString.toString() + '\n');
        }

        printStatsToFile("decode_stats.txt", statistics);

    }

    private void printStatsToFile(String fileName, Set<StatCounter> statistics) throws IOException {
        FileWriter statsOut = new FileWriter(fileName);

        for(StatCounter counter : statistics){
            statsOut.write(counter.getSymbol().toString() + ' ' + counter.getCounter() + '\n');
        }

        statsOut.close();
    }

}
