# Arranger

Predict score for mapping algorithm using web_data_processor model

Score formula is:
    
    score = sum for each class (scalar_product(v_i, v_j) sum over all pairs in this class)
    
where v_i, v_j is features vector for companies i, j from model.csv


Score for for "YANDEX" and "GOOGLE" in same class with example_model.csv will be 210.
