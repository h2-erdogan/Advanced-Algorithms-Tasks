import pandas as pd

modules_file = "data/cs modules.csv"
marks_file = "data/task1_1_marks.csv"

modules_df = pd.read_csv(modules_file, header=None, names=["Module Code", "Module Name"])

modules_df['Level'] = modules_df['Module Code'].str[-1]

marks_df = pd.read_csv(marks_file, header=None)

reshaped_data = []
num_columns = marks_df.shape[1]

for _, row in marks_df.iterrows():
    student_id = row[0]  # First column is for the student ID
    for i in range(1, num_columns, 2):  
        if i + 1 < num_columns:  
            module_code = row[i]
            mark = row[i + 1]
            reshaped_data.append([student_id, module_code, mark])


marks_df_long = pd.DataFrame(reshaped_data, columns=['Student ID', 'Module Code', 'Mark'])

# Convert marks 
marks_df_long['Mark'] = pd.to_numeric(marks_df_long['Mark'], errors='coerce')

# Merge with module information to get levels
marks_df_long = marks_df_long.merge(modules_df, on='Module Code', how='left')


marks_df_long['Credits'] = marks_df_long['Module Code'].str.extract(r'-(\d+)-')[0].astype(float)


level_5_marks = marks_df_long[marks_df_long['Level'] == '2']
level_6_marks = marks_df_long[marks_df_long['Level'] == '3']

# Function to calculate weighted average
def weighted_average(df, best_n_credits=None):
    if df.empty:
        return 0  
    
    if best_n_credits:
        df = df.sort_values(by='Mark', ascending=False)
        total_credits = 0
        selected_rows = []
        for _, row in df.iterrows():
            if total_credits + row['Credits'] <= best_n_credits:
                selected_rows.append(row)
                total_credits += row['Credits']
        df = pd.DataFrame(selected_rows)
    
    weighted_sum = (df['Mark'] * df['Credits']).sum()
    total_credits = df['Credits'].sum()
    
    return weighted_sum / total_credits if total_credits > 0 else 0


final_results = []
for student_id in marks_df_long['Student ID'].unique():
    student_level_5 = level_5_marks[level_5_marks['Student ID'] == student_id]
    student_level_6 = level_6_marks[level_6_marks['Student ID'] == student_id]
    
    weighted_avg_5 = weighted_average(student_level_5, best_n_credits=100)
    weighted_avg_6 = weighted_average(student_level_6)
    
    # Compute final aggregate mark (3:1 weighting)
    final_aggregate = (3 * weighted_avg_6 + weighted_avg_5) / 4
    
   
    if final_aggregate >= 70:
        classification = "First Class"
    elif final_aggregate >= 60:
        classification = "Upper Second Class (2.1)"
    elif final_aggregate >= 50:
        classification = "Lower Second Class (2.2)"
    elif final_aggregate >= 40:
        classification = "Third Class"
    else:
        classification = "Fail"
    
    final_results.append([student_id, weighted_avg_5, weighted_avg_6, final_aggregate, classification])


final_results_df = pd.DataFrame(final_results, columns=[
    'Student ID', 'Level 5 Weighted Average', 'Level 6 Weighted Average', 'Final Aggregate Mark', 'Degree Classification'
])


output_file = "data/final_degree_results.csv"

final_results_df.to_csv(output_file, index=False)

print("Final results saved to:", output_file)

