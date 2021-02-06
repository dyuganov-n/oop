public class CharCounter {
    private final Character symbol;
    private Integer counter = 0;

    public CharCounter(Character symbol){
        this.symbol = symbol;
        counter = 1;
    }

    public Character getSymbol(){
        return symbol;
    }

    public Integer getCounter() {
        return counter;
    }

    public void increaseCnt() {
        ++counter;
    }

    public void decrease() {
        --counter;
    }

    public boolean equals(Object other) {
        if(this == other) {
            return true;
        }
        if (other == null || other.getClass() != this.getClass()) {
            return false;
        }
        CharCounter sc = (CharCounter)other;
        return this.symbol.equals(sc.symbol);
    }

    public int hashCode() {
        return (int)symbol;
    }
}
