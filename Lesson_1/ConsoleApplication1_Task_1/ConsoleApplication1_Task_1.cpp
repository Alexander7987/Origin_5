#include "iostream"

struct Query {
    std::string name = "";
    std::string description = "";

    std::string columns = "";
    std::string table_name = "";
    std::string parameters = "";

    std::string body_query = "";

    int counter_for_metod_AddColumn = 0;
};


class SqlSelectQueryBuilder {
public:
    explicit SqlSelectQueryBuilder(const std::string& builder_name) {
        query.name = builder_name;
        query.description = "This is " + query.name;
    }

    SqlSelectQueryBuilder& AddColumn(const std::string& name_column) noexcept {
        if (query.columns != "")
        {
            query.columns += ", ";
            query.columns += name_column;
            query.counter_for_metod_AddColumn++;
            return *this;
        }
        else
        {
            query.columns += name_column;
            query.counter_for_metod_AddColumn++;
            return *this;
        }
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& table_name_) {
        query.table_name = table_name_;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& name_parameter, const std::string& value) {
        if (query.parameters != "")
        {
            query.parameters += " AND ";
            query.parameters += name_parameter + " = " + value;
            return *this;
        }
        else
        {
            query.parameters += name_parameter + " = " + value;
            return *this;
        }
    }

    std::string& BuildQuery() {
        if (query.counter_for_metod_AddColumn == 0)
        {
            query.body_query = "SELECT* " + query.table_name + " WHERE " + query.parameters + ";";
            return query.body_query;
        }
        else
        {
            query.body_query = "SELECT " + query.columns + " FROM " + query.table_name + " WHERE " + query.parameters + ";";
            return query.body_query;
        }
        return query.body_query;
    }

private:
    Query query;
};


int main() {
    SqlSelectQueryBuilder query_builder("VeryImportantBuilder");
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students").AddFrom("teachers");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");

    std::cout << query_builder.BuildQuery();
    return 0;
}