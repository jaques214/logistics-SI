# logistics-SI

**Tema**

As empresas de distribuição e logística representam uma atividade muito importante no atual sistema económico.
Um forte impulsionador terá sido a possibilidade de comprar os mais variados artigos pela Internet e aguardar comodamente a sua chegada numa morada definida.
Esta aplicação representa um sistema de informação básico para gerir as operações de logística de uma empresa de distribuição.
O cálculo dos custos de transporte varia de acordo com o tipo de artigos, nomeadamente se estes carecem de cuidados especiais (por exemplo, contém partes frágeis), se a encomenda é volumosa ou se é de caráter urgente. Um cliente no sistema representa uma pessoa/entidade que pretende usufruir dos serviços de transporte. Este insere todos os dados referentes à encomenda que pretende enviar e obtém o custo de envio. O Diretor é a entidade máxima da empresa de transportes que tem acesso a toda a informação de todos os clientes e encomendas transportadas. Pode ainda alterar preços e verificar o estado da faturação de cada mês, entre outros. Neste sistema considera-se que o login apenas requer o NIF para identificar o utilizador como Cliente ou Diretor, não sendo necessário validar passwords.

**Funcionalidades:**

**Gestão de utilizadores -** o cliente pode criar, editar e remover o seu perfil de utilizador. Apesar da remoção de um cliente apenas remover a "marcação", não 
permitindo novos acessos, ou introdução de novas encomendas. O Diretor pode realizar qualquer uma das operações de manipulação de clientes inclusive reativar um cliente removido.

**Gestão de encomendas -** o cliente pode acrescentar uma nova encomenda a transportar, identificando a origem e destino, bem como a distância em quilómetros. Ainda é possível consultar o estado das encomendas, permitindo alterar/cancelar encomendas não expedidas. O Diretor atualiza o estado das encomendas sempre que estas forem expedidas.

**Gestão de preços -** o cliente pode consultar os preços tabelados para a realização de um transporte. O diretor é capaz de criar/editar a tabela de preços (incluindo o custo por quilómetro). A alteração de preços não se reflete nas encomendas já inseridas.

**Geração de faturas -** a aplicação é capaz de gerar/reimprimir a fatura para um cliente específico de um dado mês. A fatura deve ser gerada no ecrã e/ou escrita para ficheiro e deve conter a listagem de todas as encomendas expedidas nesse mês, com identificação da hora e do(s) artigo(s) transportados

**Persistência de dados -** a aplicação guarda/carrega dados em/de ficheiro, permitindo persisti-los ao longo de diferentes utilizações, de forma a possibilitar a leitura e gravação a qualquer momento através da respetiva escolha no menu de opções.
