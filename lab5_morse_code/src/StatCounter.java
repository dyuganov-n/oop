import java.io.FileWriter;
import java.io.IOException;
import java.util.HashSet;
import java.util.Set;

public class StatCounter {
    private Set<CharCounter> statistics = null;

    public StatCounter(){
        statistics = new HashSet<CharCounter>();
    }

    public void add(Character character){
        if(!statistics.add(new CharCounter(character))){
            for (CharCounter counter : statistics) {
                if(counter.getSymbol().equals(character)){
                    counter.increaseCnt();
                }
            }
        }
    }

    public void printToFile(String fileName) throws IOException {
        try (FileWriter statsOut = new FileWriter(fileName)) {
            for(CharCounter counter : statistics){
                statsOut.write(counter.getSymbol().toString() + ' ' + counter.getCounter() + '\n');
            }
        }
    }
}
