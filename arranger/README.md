# Arranger

Predict score for mapping algorithm using web_data_processor model

Score formula is:
    
    score = sum for each class (scalar_product(v_i, v_j) sum over all pairs in this class)
    
Where v_i, v_j is features vector for companies i, j from model.csv
