# Arranger

Predict score for mapping algorithm using web_data_processor model

Score formula is:
$$
    \sum_{c_i in classes} \sum_{all pairs over c_i} v_i \dot v_j
$$
Where $v_i, v_j$ is features vector for companies $i, j$ from model.csv
