import java.io.IOException;

/**
 * Created by sude on 2.1.2017.
 */
public interface Bigram<T> {

    public abstract void readFile(String filename) throws myExceptions, IOException;
    public abstract int numGrams();

    public abstract int numOfGrams(T firstElement, T secondElement);

}

