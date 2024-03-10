#include "iostream"
#include "map"
#include "vector"

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

    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept
    {
        if (query.columns != "")
        {
            for (auto const& t : columns)
            {          
                query.columns += ", ";
                query.columns += t;
            }
            query.counter_for_metod_AddColumn++;
            return *this;
        }
        else
        {
            for (auto const& t : columns)
            {
                query.columns += t;   
                query.columns += ", ";
            }
            if (query.columns[query.columns.size() - 1] == ' ')
            {
                query.columns.resize(query.columns.size() - 2);
            }
            query.counter_for_metod_AddColumn++;
            return *this;
        }
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& table_name_) {
        query.table_name = table_name_;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept
    {
        if (query.parameters != "")
        {
            for (const auto& [key, value] : kv)
            {
                query.parameters += " AND ";
                query.parameters += key + " = " + value;
            }         
            return *this;
        }
        else
        {
            for (const auto& [key, value] : kv)
            {
                query.parameters += key + " = " + value;
                query.parameters += " AND ";

            }
            if (query.parameters[query.parameters.size() - 1] == ' ')
            {
                query.parameters.resize(query.parameters.size() - 5);
            }
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
    query_builder.AddFrom("students").AddFrom("teachers");

    std::map<std::string, std::string> condition;
    condition.emplace("id","42");
    condition.emplace("name", "John");
    query_builder.AddWhere(condition);

    std::vector<std::string> columns;
    columns.push_back("name");
    columns.push_back("phone");
    query_builder.AddColumns(columns);

    std::cout << query_builder.BuildQuery();
    return 0;
}