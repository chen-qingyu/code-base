import time
import torch
import torchvision
import matplotlib.pyplot as plt


BATCH_SIZE = 64  # 每个批次的数据量
EPOCHS = 2  # 训练轮数
LEARNING_RATE = 0.001  # 学习率
SHOW_IMAGES = 4  # 展示测试图片的数量
DEVICE = torch.device("cuda" if torch.cuda.is_available() else "cpu")  # 训练设备


class Net(torch.nn.Module):
    def __init__(self):
        super().__init__()
        self.layers = torch.nn.Sequential(
            torch.nn.Linear(28 * 28, 64),
            torch.nn.ReLU(),
            torch.nn.Linear(64, 64),
            torch.nn.ReLU(),
            torch.nn.Linear(64, 64),
            torch.nn.ReLU(),
            torch.nn.Linear(64, 10),
            torch.nn.LogSoftmax(dim=1),
        )

    def forward(self, x):
        return self.layers(x)


def get_loader(train):
    tf = torchvision.transforms.ToTensor()
    ds = torchvision.datasets.MNIST("", train, transform=tf, download=True)
    return torch.utils.data.DataLoader(ds, batch_size=BATCH_SIZE, shuffle=True)


def evaluate(loader, net):
    net.eval()
    n_correct, n_total, total_loss = 0, 0, 0.0
    criterion = torch.nn.NLLLoss()
    with torch.no_grad():
        for x, y in loader:
            x, y = x.to(DEVICE), y.to(DEVICE)
            out = net(x.view(-1, 28 * 28))
            total_loss += criterion(out, y).item() * x.size(0)
            n_correct += (out.argmax(1) == y).sum().item()
            n_total += y.size(0)
    net.train()
    return n_correct / n_total, total_loss / n_total


def main():
    print(f"Using device: {DEVICE}")

    start_time = time.time()
    train_loader, test_loader = get_loader(True), get_loader(False)
    net = Net().to(DEVICE)
    opt = torch.optim.Adam(net.parameters(), lr=LEARNING_RATE)
    train_losses, test_losses, test_accs = [], [], []
    acc, test_loss = evaluate(test_loader, net)
    print(f"Initial accuracy: {acc:.4f}, test loss: {test_loss:.4f}")

    for epoch in range(EPOCHS):
        running_loss = 0.0
        for x, y in train_loader:
            x, y = x.to(DEVICE), y.to(DEVICE)
            opt.zero_grad()
            loss = torch.nn.functional.nll_loss(net(x.view(-1, 28 * 28)), y)
            loss.backward()
            opt.step()
            running_loss += loss.item() * x.size(0)
        train_losses.append(running_loss / len(train_loader.dataset))  # type: ignore
        acc, test_loss = evaluate(test_loader, net)
        test_accs.append(acc)
        test_losses.append(test_loss)
        print(f"Epoch {epoch + 1}: train loss={train_losses[-1]:.4f}, test loss={test_loss:.4f}, accuracy={acc:.4f}")
    print(f"Total time: {time.time() - start_time:.2f} seconds")

    # 展示损失和准确率曲线
    plt.figure()
    plt.plot(range(1, EPOCHS + 1), train_losses, label="Train Loss")
    plt.plot(range(1, EPOCHS + 1), test_losses, label="Test Loss")
    plt.plot(range(1, EPOCHS + 1), test_accs, label="Test Accuracy")
    plt.xlabel("Epoch")
    plt.legend()
    plt.title("Training Progress")
    plt.show()

    # 展示部分测试图片及预测
    net.eval()
    shown = 0
    _, axes = plt.subplots(1, SHOW_IMAGES, figsize=(3 * SHOW_IMAGES, 3))
    for x, y in test_loader:
        x, y = x.to(DEVICE), y.to(DEVICE)
        preds = net(x.view(-1, 28 * 28)).argmax(1)
        for i in range(x.size(0)):
            if shown >= SHOW_IMAGES:
                break
            axes[shown].imshow(x[i].cpu().view(28, 28), cmap="gray")
            axes[shown].set_title(f"Pred: {int(preds[i])}\nLabel: {int(y[i])}")
            axes[shown].axis("off")
            shown += 1
        if shown >= SHOW_IMAGES:
            break
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
