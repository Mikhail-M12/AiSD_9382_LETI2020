import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

lg = {
    'count': [x for x in range(1, 10000, 1)],
    'val': [np.log2(x) for x in range(1, 10000, 1)]
}
df1 = pd.read_csv('research_add.csv')
df2 = pd.read_csv('research_delete.csv')

fig = plt.figure()
fig.subplots_adjust()

ax1 = fig.add_subplot(111)
# plt.title('Количество вызовов операции вставки в худшем случае')
# plt.title('Количество вызовов операции вставки в случайном дереве')
ax1.set_xlabel('Количество элементов в дереве')
ax1.set_ylabel('Количество операций для вставки')
ax1.plot(df1['tree_size'], df1['op_count'])
ax1.plot(lg['count'], lg['val'])
ax1.grid(color='gray', linestyle=':', linewidth=0.3)
ax1.legend(['avl tree insert', 'log2(n)'], loc=2)
# plt.savefig("research_add.png")
plt.savefig("research_add_random.png")

# ax1 = fig.add_subplot(111)
# plt.title('Количество вызовов операции удаления в худшем случае')
# plt.title('Количество вызовов операции удаления в случайном дереве')
# ax1.set_xlabel('Количество элементов в дереве')
# ax1.set_ylabel('Количество операций для удаления')
# ax1.plot(df2['tree_size'], df2['op_count'])
# ax1.plot(lg['count'], lg['val'])
# ax1.grid(color='gray', linestyle=':', linewidth=0.3)
# ax1.legend(['avl tree remove', 'log2(n)'], loc=2)
# plt.savefig("research_delete.png")
# plt.savefig("research_delete_random.png")
#plt.show()