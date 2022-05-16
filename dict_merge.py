def dict_merge(*dicts: dict) -> dict:
    """ Merge multiple dictionaries """
    new_dict = dict()
    for d in dicts:
        for k, v in d.items():
            if k not in new_dict.keys():  # key not in dict
                new_dict[k] = v
            else:  # key in dict
                if isinstance(new_dict[k], list) and v not in new_dict[k]:  # multiple value
                    new_dict[k].append(v)
                elif v != new_dict[k]:  # single value
                    new_dict[k] = [new_dict[k], v]
    return new_dict


dic1 = {"A": 1, "B": 2, "C": 3, "D": 4}
dic2 = {"A": 123, "B": 2}
dic3 = {"A": 456, "C": 3}
dic4 = {"A": 789, "D": 4}
dic5 = {"A": [1], "B": [2], "C": [3], "D": [4]}
dic6 = {"A": [], "B": [], "C": [], "D": []}
dic = dict_merge(dic1, dic2, dic3, dic4, dic5, dic6)
print(dic)
