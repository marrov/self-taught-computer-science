# Rebalance

## Description:

### Video Demo:  https://youtu.be/vBTHyhAC0q0

### Overview

This project aims to provide a website to track an all-fund portfolio that one can invest in through the Spanish bank MyInvestor. The website is built in python Flask, HTML, and CSS. The Bootstrap framework is used for styling and an online template was employed as a starting point. To store the user and portfolio data, the models are developed in Sqlite 3 using SQLAlchemy. The model implements a simple many-to-many relationship and password security is handled by hashing. The fund data is obtained directly from MyInvestor by interfacing their API with the requests library in python. The response JSON is parsed before inputting the information into a python class which is then employed in the python backend.

### Review of the files

In the main folder you can find the basic files for running. `environment.yml` and `requirements.txt` contains two different ways of obtaining the libraries needed to run.

`main.py` is the main executable and calls the function that creates the Flask application from the main module `rebalance`.

Inside the `rebalance` folder we find two folders, `static` and `templates`:

`static` includes assets, such as images, the main CSS file in `css/styles.css` and two javascript files. The CSS stylesheet has been mainly based on this [online template](https://startbootstrap.com/template/sb-admin). The javascript files include the definition for the styles of the [tables employed](https://github.com/fiduswriter/Simple-DataTables/wiki) and a file calles `scripts.js`. This file mainly holds the code to toggle the navbar and to create and delete rows dinamically from the ideal portfolio builder.

`templates` includes the HTML for the different pages employed. As they are made to work with a Flask backend, they emplyed `jinja` syntax. The HTML pages can be divided into home, login/signup, dashboards and layouts. These have different functions in the flow of the website. The layouts are the base which others extend and are made to share the basic structure as well as navbar and sidebar, when appropriate. The dashboards are used to inform the user about the state of their portfolio if the have one and can build one if they don't.

Finally the python file inside the `rebalance` folder include `init.py`, `auth.py`, `funds.py`, `models.py`, `rebalance.db` and `views.py`
- `init.py` gets  executed when calling the rebalance module. This file creates the Flask app and the Sqlite 3 database `rebalance.db` if it doesnt exist. 
- `auth.py` handles the logic to authenticate and register users for the rebalance website.
- `funds.py` deals with the request and parsing of the fund information in the MyInvestor API call into a python class.
- `models.py` defines the relationship that exists between the different parts of the database. This includes the users, funds, real and ideal portfolio. Here the latter two are table required to define the many-to-many relationship between users and funds.
- `views.py` finally handles the backend logic for the different dahsboard pages. This basically forces the user into the following flow: create an ideal portfolio with target allocations, define his/her real portfolio with his/her current allocation and view a summary of the steps required to correctly relabance the real portfolio. 