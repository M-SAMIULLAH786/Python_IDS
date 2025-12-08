import os
import json
import streamlit as st # type: ignore
import pandas as pd # type: ignore
import numpy as np # type: ignore
import seaborn as sns # type: ignore
import matplotlib.pyplot as plt # type: ignore
from sklearn.pipeline import Pipeline
from sklearn.impute import SimpleImputer
from sklearn.preprocessing import StandardScaler, OneHotEncoder
from sklearn.compose import ColumnTransformer
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import mean_squared_error, r2_score
import joblib # type: ignore


st.set_page_config(page_title="Sleep Health & Lifestyle Analysis", layout="wide")

# Sidebar Navigation
st.sidebar.title("📊 Sleep Health Analyzer")

# Display banner image in sidebar if available
if os.path.exists("sleep_health_banner.png"):
    st.sidebar.image("sleep_health_banner.png", use_container_width=True)

st.sidebar.markdown("---")
st.sidebar.header("📱 Navigation")
st.sidebar.markdown("**Choose a section**")

page = st.sidebar.radio(
    "",
    ["📚 Introduction", "📊 EDA Dashboard", "🔮 Predict Sleep Quality", "📝 Conclusion"],
    label_visibility="collapsed"
)

st.sidebar.markdown("---")
st.sidebar.header("Upload Your CSV Dataset")
uploaded_file = st.sidebar.file_uploader("Choose a CSV file", type=["csv"])

# Load dataset
if uploaded_file is not None:
    df = pd.read_csv(uploaded_file)
else:
    # Default dataset (ensure this file exists in the project folder)
    df = pd.read_csv("Sleep_health_and_lifestyle_dataset.csv")

# keep original copy for reference
df_original = df.copy()

MODEL_PATH = "sleep_pipeline.pkl"
FEATURES_META = "feature_meta.json"

# Helper functions
def build_pipeline(X_cols, df_ref):
    num_cols = df_ref[X_cols].select_dtypes(include=[np.number]).columns.tolist()
    cat_cols_local = [c for c in X_cols if c in df_ref.select_dtypes(include=['object','category']).columns]

    num_pipeline = Pipeline([('imputer', SimpleImputer(strategy='median')), ('scaler', StandardScaler())])
    cat_pipeline = Pipeline([('imputer', SimpleImputer(strategy='most_frequent')), ('onehot', OneHotEncoder(handle_unknown='ignore'))])

    preprocessor = ColumnTransformer([('num', num_pipeline, num_cols), ('cat', cat_pipeline, cat_cols_local)], remainder='drop')

    pipeline = Pipeline([('preprocessor', preprocessor), ('model', RandomForestRegressor(n_estimators=100, random_state=42))])
    return pipeline

def load_pipeline_if_exists():
    if "pipeline" not in st.session_state:
        if os.path.exists(MODEL_PATH):
            st.session_state['pipeline'] = joblib.load(MODEL_PATH)
        else:
            st.session_state['pipeline'] = None
    if "feature_meta" not in st.session_state:
        if os.path.exists(FEATURES_META):
            with open(FEATURES_META,'r') as fh:
                st.session_state['feature_meta'] = json.load(fh)
        else:
            st.session_state['feature_meta'] = None

load_pipeline_if_exists()

# ==================== PAGE: INTRODUCTION ====================
if page == "📚 Introduction":
    st.title("📚 Sleep Health & Lifestyle Analysis")
    
    # Display banner image if available
    if os.path.exists("sleep_health_banner.png"):
        st.image("sleep_health_banner.png", use_container_width=True)
    
    st.markdown("""
    ### Project Overview
    This project analyzes the **Sleep Health and Lifestyle Dataset** to understand the relationships between 
    sleep patterns, lifestyle factors, and health outcomes.
    
    ### Goals
    - ✅ Perform comprehensive Exploratory Data Analysis (EDA) with 15+ different analyses
    - ✅ Preprocess data using robust pipelines (imputation, encoding, scaling)
    - ✅ Train and evaluate machine learning models (Random Forest Regressor)
    - ✅ Enable runtime predictions via an interactive Streamlit interface
    
    ### Dataset Information
    - **Name:** Sleep Health and Lifestyle Dataset
    - **Rows:** {rows}
    - **Columns:** {cols}
    
    ### Course Information
    - **Course:** Introduction to Data Science (IDS F24)
    
    - **Student:** Muhammad SamiUllah
    
    ---
    
    ### Quick Start
    1. 📊 Navigate to **EDA Dashboard** to explore the data
    2. 🔮 Go to **Predict Sleep Quality** to train models and make predictions
    3. 📝 Review **Conclusion** for key takeaways
    """.format(rows=df.shape[0], cols=df.shape[1]))
    
    st.subheader("📋 Dataset Preview")
    st.dataframe(df.head(10))

# ==================== PAGE: EDA DASHBOARD ====================
elif page == "📊 EDA Dashboard":
    st.title("📊 Exploratory Data Analysis Dashboard")
    
    # Prepare numeric and categorical data
    numeric_df = df.select_dtypes(include=[np.number])
    cat_cols = df.select_dtypes(include=['object', 'category']).columns.tolist()
    
    # Dataset Summary
    st.subheader("📈 Dataset Summary")
    col1, col2, col3 = st.columns(3)
    with col1:
        st.metric("Total Rows", df.shape[0])
    with col2:
        st.metric("Total Columns", df.shape[1])
    with col3:
        st.metric("Missing Values", df.isnull().sum().sum())
    
    st.write(df.describe(include='all'))
    
    # Missing Values Analysis
    st.subheader("🔍 Missing Values Analysis")
    missing_vals = df.isnull().sum()
    if missing_vals.sum() > 0:
        st.dataframe(missing_vals[missing_vals > 0].to_frame('Missing Count'))
    else:
        st.success("No missing values found!")
    
    # Correlation Heatmap
    st.subheader("🔥 Correlation Heatmap (numeric features)")
    if numeric_df.shape[1] > 1:
        fig, ax = plt.subplots(figsize=(10,6))
        sns.heatmap(numeric_df.corr(), annot=True, cmap="coolwarm", ax=ax, center=0)
        st.pyplot(fig)
    else:
        st.write("Not enough numeric columns for correlation heatmap.")
    
    # Feature Distributions
    st.subheader("📊 Feature Distributions (numeric)")
    for col in numeric_df.columns:
        fig, ax = plt.subplots(figsize=(7,4))
        sns.histplot(numeric_df[col].dropna(), bins=20, kde=True, color='purple', ax=ax)
        ax.set_title(f'Distribution of {col}')
        st.pyplot(fig)
    
    # Boxplots
    st.subheader("📦 Boxplots (numeric)")
    for col in numeric_df.columns:
        fig, ax = plt.subplots(figsize=(6,3))
        sns.boxplot(x=numeric_df[col].dropna(), ax=ax, color='skyblue')
        ax.set_title(f'Boxplot of {col}')
        st.pyplot(fig)
    
    # Pairplot
    st.subheader("🔗 Pairwise Feature Relationships")
    if numeric_df.shape[1] <= 6:
        fig = sns.pairplot(numeric_df.dropna(), diag_kind='kde', corner=True)
        st.pyplot(fig)
    else:
        st.write(f"Too many numeric features ({numeric_df.shape[1]}) for full pairplot. Showing first 5 columns.")
        fig = sns.pairplot(numeric_df.iloc[:, :5].dropna(), diag_kind='kde', corner=True)
        st.pyplot(fig)
    
    # Skewness and Kurtosis
    st.subheader("📐 Skewness and Kurtosis Analysis")
    skew_kurt = pd.DataFrame({
        'Feature': numeric_df.columns,
        'Skewness': numeric_df.skew(),
        'Kurtosis': numeric_df.kurtosis()
    })
    st.dataframe(skew_kurt)
    
    # Categorical summaries
    if len(cat_cols) > 0:
        st.subheader("🏷️ Categorical Value Counts")
        for col in cat_cols:
            st.write(f"**{col}** - Unique: {df[col].nunique()}")
            st.write(df[col].value_counts().head(10))
    
    # Grouped Aggregations
    st.subheader("📊 Grouped Aggregations")
    if len(cat_cols) > 0 and len(numeric_df.columns) > 0:
        groupby_col = st.selectbox("Select categorical column to group by", cat_cols, key='groupby')
        agg_col = st.selectbox("Select numeric column to aggregate", numeric_df.columns.tolist(), key='aggcol')
        grouped = df.groupby(groupby_col)[agg_col].agg(['mean', 'median', 'std', 'count'])
        st.write(f"Aggregated statistics of **{agg_col}** grouped by **{groupby_col}**:")
        st.dataframe(grouped)
    else:
        st.write("No categorical or numeric columns available for grouping.")
    
    # Outlier detection
    st.subheader("⚠️ Outlier Detection (IQR Method)")
    outlier_summary = {}
    for col in numeric_df.columns:
        q1 = numeric_df[col].quantile(0.25)
        q3 = numeric_df[col].quantile(0.75)
        iqr = q3 - q1
        lower = q1 - 1.5 * iqr
        upper = q3 + 1.5 * iqr
        outliers = numeric_df[(numeric_df[col] < lower) | (numeric_df[col] > upper)][col].count()
        outlier_summary[col] = int(outliers)
    st.write(outlier_summary)

# ==================== PAGE: PREDICT SLEEP QUALITY ====================
elif page == "🔮 Predict Sleep Quality":
    st.title("🔮 Predict Sleep Quality")
    
    tab1, tab2 = st.tabs(["🏋️ Train Model", "🎯 Make Predictions"])
    
    with tab1:
        st.subheader("Model Training - Random Forest with Pipeline")
        
        # Only allow numeric columns as target for regression
        numeric_cols = df.select_dtypes(include=[np.number]).columns.tolist()
        
        if len(numeric_cols) == 0:
            st.error("❌ No numeric columns found in the dataset. Please upload a dataset with numeric target variables.")
        else:
            target = st.selectbox("Select Target Variable (numeric only)", options=numeric_cols)
            all_features = df.columns.tolist()
            features = st.multiselect("Select Feature Columns", options=[f for f in all_features if f != target], default=[f for f in all_features if f != target])
        
            if st.button("🚀 Train Model"):
                if len(features) == 0:
                    st.warning("Please select at least one feature!")
                else:
                    # Clean data: remove rows where target has missing values
                    df_clean = df[[target] + features].dropna(subset=[target])
                    
                    if len(df_clean) == 0:
                        st.error(f"❌ No valid data found. The target variable '{target}' has all missing values!")
                    elif len(df_clean) < 10:
                        st.error(f"❌ Not enough data after removing missing values. Only {len(df_clean)} rows available (minimum 10 needed).")
                    else:
                        X = df_clean[features]
                        y = df_clean[target]
                        
                        if len(df_clean) < len(df):
                            st.info(f"ℹ️ Removed {len(df) - len(df_clean)} rows with missing target values. Training with {len(df_clean)} rows.")

                        pipeline = build_pipeline(features, df)

                        with st.spinner("Training model..."):
                            X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
                            pipeline.fit(X_train, y_train)
                            y_pred = pipeline.predict(X_test)

                    st.success("✅ Model trained successfully!")

                    # Metrics
                    col1, col2 = st.columns(2)
                    mse = mean_squared_error(y_test, y_pred)
                    r2 = r2_score(y_test, y_pred)
                    
                    with col1:
                        st.metric("Mean Squared Error", f"{mse:.2f}")
                    with col2:
                        st.metric("R² Score", f"{r2:.3f}")

                    # Cross-validation
                    with st.spinner("Running cross-validation (3-fold)..."):
                        scores = cross_val_score(pipeline, X, y, cv=3, scoring='r2')
                    st.write(f"**3-fold CV R² scores:** {scores.round(3)} | **Mean:** {scores.mean():.3f}")

                    # Feature Importance
                    st.subheader("📊 Feature Importance")
                    model_rf = pipeline.named_steps['model']
                    
                    # Get feature names after preprocessing
                    preprocessor = pipeline.named_steps['preprocessor']
                    num_cols = df[features].select_dtypes(include=[np.number]).columns.tolist()
                    cat_cols_local = [c for c in features if c in df.select_dtypes(include=['object','category']).columns]
                    
                    feature_names = num_cols.copy()
                    if len(cat_cols_local) > 0:
                        onehot = preprocessor.named_transformers_['cat'].named_steps['onehot']
                        cat_features = onehot.get_feature_names_out(cat_cols_local)
                        feature_names.extend(cat_features)
                    
                    importances = model_rf.feature_importances_
                    indices = np.argsort(importances)[::-1][:15]  # top 15
                    
                    fig, ax = plt.subplots(figsize=(8,6))
                    ax.barh(range(len(indices)), importances[indices], color='teal')
                    ax.set_yticks(range(len(indices)))
                    ax.set_yticklabels([feature_names[i] for i in indices])
                    ax.set_xlabel('Importance')
                    ax.set_title('Top 15 Feature Importances (Random Forest)')
                    ax.invert_yaxis()
                    st.pyplot(fig)

                    # Save pipeline and metadata
                    joblib.dump(pipeline, MODEL_PATH)
                    # Save feature metadata (types and defaults)
                    meta = {}
                    for f in features:
                        if f in df.select_dtypes(include=[np.number]).columns:
                            meta[f] = {"type": "numeric", "median": float(df[f].median())}
                        else:
                            meta[f] = {"type": "categorical", "values": df[f].dropna().unique().tolist(), "mode": str(df[f].mode().iloc[0])}
                    with open(FEATURES_META, 'w') as fh:
                        json.dump({"features": features, "target": target, "meta": meta}, fh)

                    st.success(f"💾 Pipeline saved to `{MODEL_PATH}` and feature metadata saved to `{FEATURES_META}`")
                    
                    # Reload pipeline
                    st.session_state['pipeline'] = pipeline
                    st.session_state['feature_meta'] = {"features": features, "target": target, "meta": meta}
    
    with tab2:
        st.subheader("Make Real-Time Predictions")
        
        if st.session_state.get('pipeline') is None:
            st.info('ℹ️ No trained model found. Please train a model in the **Train Model** tab first.')
        else:
            st.write('Enter feature values to make a prediction:')
            feature_inputs = {}
            meta = st.session_state.get('feature_meta', {})
            features_meta = meta.get('meta') if meta else None
            features_list = meta.get('features') if meta else []
            target_var = meta.get('target', 'target')

            # Create input widgets
            for f in features_list:
                if features_meta and features_meta.get(f, {}).get('type') == 'numeric':
                    default = features_meta[f].get('median', 0)
                    feature_inputs[f] = st.number_input(f, value=float(default), key=f"pred_{f}")
                else:
                    # categorical
                    opts = features_meta[f].get('values') if features_meta and features_meta.get(f) else df_original[f].dropna().unique().tolist()
                    if len(opts) == 0:
                        feature_inputs[f] = st.text_input(f, value='', key=f"pred_{f}")
                    else:
                        feature_inputs[f] = st.selectbox(f, options=opts, index=0, key=f"pred_{f}")

            if st.button('🎯 Predict'):
                input_df = pd.DataFrame([feature_inputs])
                try:
                    pred = st.session_state['pipeline'].predict(input_df)
                    st.success(f"### Predicted **{target_var}**: {pred[0]:.2f}")
                except Exception as e:
                    st.error(f"❌ Prediction failed: {e}")

# ==================== PAGE: CONCLUSION ====================
elif page == "📝 Conclusion":
    st.title("📝 Conclusion & Key Takeaways")
    
    st.markdown("""
    ### 🎯 Key Takeaways
    
    1. **Comprehensive EDA:** We performed 15+ analyses including summary stats, distributions, boxplots, 
       correlation heatmap, pairplot, skewness/kurtosis, outlier detection, value counts, and grouped aggregations.
    
    2. **Robust Preprocessing:** Used sklearn Pipelines with ColumnTransformer to handle missing values (median/mode imputation), 
       encode categorical variables (OneHotEncoder), and scale numeric features (StandardScaler).
    
    3. **Model Training & Evaluation:** Trained a Random Forest Regressor with cross-validation, evaluated with MSE and R² metrics, 
       and visualized feature importances to understand key predictors.
    
    4. **Runtime Predictions:** Built a dynamic prediction interface that loads the trained pipeline and accepts user inputs 
       (both numeric and categorical) to generate real-time predictions.
    
    5. **Reproducibility:** All preprocessing and modeling steps are encapsulated in a saved pipeline (`sleep_pipeline.pkl`) 
       and feature metadata (`feature_meta.json`) for easy reuse and deployment.
    
    ---
    
    ### 🚀 Next Steps
    - Experiment with other models (XGBoost, Gradient Boosting, Linear Regression)
    - Hyperparameter tuning via GridSearchCV or RandomizedSearchCV
    - Add SHAP values for local prediction explanations
    - Deploy the app to Streamlit Cloud for public access
    
    ---
    
    ### 👨‍💻 Project Information
    - **Student Name:** Muhammad SamiUllah
    - **Course:** Introduction to Data Science (IDS F24)
  
    
    ---
    
    ### 📊 Project Checklist
    - ✅ Unique dataset selected
    - ✅ 15+ EDA analyses performed
    - ✅ Data preprocessing implemented
    - ✅ Machine learning model trained
    - ✅ Runtime predictions enabled
    - ✅ Interactive Streamlit application
    - ✅ Complete documentation
    
    **Thank you for reviewing this project!** 🎓
    """)
