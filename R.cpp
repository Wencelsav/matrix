#include <cmath>
 
// Функция, производящая обращение матрицы.
// Принимает:
//     matrix - матрица для обращения
//     result - матрица достаточного размера для вмещения результата
//     size   - размерность матрицы
// Возвращает:
//     true в случае успешного обращения, false в противном случае
bool inverse(double **matrix, double **result, int size)
{   
    // Изначально результирующая матрица является единичной
    // Заполняем единичную матрицу
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
            result[i][j] = 0.0;
        
        result[i][i] = 1.0;
    }
    
    // Копия исходной матрицы
    double **copy = new double *[size]();
    
    // Заполняем копию исходной матрицы
    for (int i = 0; i < size; ++i)
    {
        copy[i] = new double [size];
        
        for (int j = 0; j < size; ++j)
            copy[i][j] = matrix[i][j];
    }
    
    // Проходим по строкам матрицы (назовём их исходными)
    // сверху вниз. На данном этапе происходит прямой ход
    // и исходная матрица превращается в верхнюю треугольную
    for (int k = 0; k < size; ++k)
    {
        // Если элемент на главной диагонали в исходной
        // строке - нуль, то ищем строку, где элемент
        // того же столбца не нулевой, и меняем строки
        // местами
        if (fabs(copy[k][k]) < 1e-8)
        {
            // Ключ, говорязий о том, что был произведён обмен строк
            bool changed = false;
            
            // Идём по строкам, расположенным ниже исходной
            for (int i = k + 1; i < size; ++i)
            {
                // Если нашли строку, где в том же столбце
                // имеется ненулевой элемент
                if (fabs(copy[i][k]) > 1e-8)
                {
                    // Меняем найденную и исходную строки местами
                    // как в исходной матрице, так и в единичной
                    std::swap(copy[k],   copy[i]);
                    std::swap(result[k], result[i]);
                    
                    // Взводим ключ - сообщаем о произведённом обмене строк
                    changed = true;
                    
                    break;
                }
            }
            
            // Если обмен строк произведён не был - матрица не может быть
            // обращена
            if (!changed)
            {
                // Чистим память
                for (int i = 0; i < size; ++i)
                    delete [] copy[i];
                
                delete [] copy;
                
                // Сообщаем о неудаче обращения
                return false;
            }
        }
        
        // Запоминаем делитель - диагональный элемент
        double div = copy[k][k];
        
        // Все элементы исходной строки делим на диагональный
        // элемент как в исходной матрице, так и в единичной
        for (int j = 0; j < size; ++j)
        {
            copy[k][j]   /= div;
            result[k][j] /= div;
        }
        
        // Идём по строкам, которые расположены ниже исходной
        for (int i = k + 1; i < size; ++i)
        {
            // Запоминаем множитель - элемент очередной строки,
            // расположенный под диагональным элементом исходной
            // строки
            double multi = copy[i][k];
            
            // Отнимаем от очередной строки исходную, умноженную
            // на сохранённый ранее множитель как в исходной,
            // так и в единичной матрице
            for (int j = 0; j < size; ++j)
            {
                copy[i][j]   -= multi * copy[k][j];
                result[i][j] -= multi * result[k][j];
            }
        }
    }
    
    // Проходим по вернхней треугольной матрице, полученной
    // на прямом ходе, снизу вверх
    // На данном этапе происходит обратный ход, и из исходной
    // матрицы окончательно формируется единичная, а из единичной -
    // обратная
    for (int k = size - 1; k > 0; --k)
    {
        // Идём по строкам, которые расположены выше исходной
        for (int i = k - 1; i + 1 > 0; --i)
        {
            // Запоминаем множитель - элемент очередной строки,
            // расположенный над диагональным элементом исходной
            // строки
            double multi = copy[i][k];
            
            // Отнимаем от очередной строки исходную, умноженную
            // на сохранённый ранее множитель как в исходной,
            // так и в единичной матрице
            for (int j = 0; j < size; ++j)
            {
                copy[i][j]   -= multi * copy[k][j];
                result[i][j] -= multi * result[k][j];
            }
        }
    }
    
    // Чистим память
    for (int i = 0; i < size; ++i)
        delete [] copy[i];
    
    delete [] copy;
    
    // Сообщаем об успехе обращения
    return true;
}
